#include "cgroup_limit.h"

// Vérifie si un fichier ou répertoire existe
int cgroup_exists(const char *path) {
    return access(path, F_OK) != -1;
}

// Obtient la mémoire totale du système
long get_total_memory() {
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        perror("Erreur lors de la récupération des informations système");
        return -1;
    }
    return info.totalram * info.mem_unit;
}

// Crée un cgroup et applique les limites spécifiées
void create_cgroup_and_apply_limits(char *program_name, float cpu_percentage, float memory_percentage) {
    char *cgroup_path= malloc(1024*sizeof(char));
    FILE *file;

    // Construction du chemin complet du cgroup
    snprintf(cgroup_path, 1024*sizeof(char), "%s%s", CGROUP_BASE, program_name);

    // Vérifier si le cgroup existe déjà
    if (!cgroup_exists(cgroup_path)) {
        if (mkdir(cgroup_path, 0755) != 0) {
            perror("Erreur lors de la création du cgroup");
            return;
        }
    }

    // Définition du pourcentage de CPU
    char *cpu_max_path= malloc(1024*sizeof(char));
    snprintf(cpu_max_path, 1024*sizeof(char), "%s/cpu.max", cgroup_path);
    file = fopen(cpu_max_path, "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture de cpu.max");
        return;
    }
    fprintf(file, "%f %d", 100000 * cpu_percentage / 100, 100000);
    fclose(file);

    // Calcul de la limite de mémoire en fonction de la mémoire totale du système
    long total_memory = get_total_memory();
    if (total_memory == -1) {
        return;
    }
    long memory_limit = total_memory * memory_percentage / 100;

    // Ajuster la limite de mémoire pour être conservateur
    memory_limit = (memory_limit > 0) ? memory_limit - 1 : 0;

    // Définition de la limite de mémoire dans memory.max
    char *memory_max_path= malloc(1024*sizeof(char));
    snprintf(memory_max_path, 1024*sizeof(char), "%s/memory.max", cgroup_path);
    file = fopen(memory_max_path, "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture de memory.max");
        return;
    }
    fprintf(file, "%ld", memory_limit);
    fclose(file);

    // Obtention des PIDs du programme
    char *pgrep_cmd= malloc(1024*sizeof(char));
    snprintf(pgrep_cmd, 1024*sizeof(char), "pgrep %s", program_name);

    // Exécution de la commande pgrep pour obtenir les PIDs
    FILE *pgrep_output = popen(pgrep_cmd, "r");
    if (pgrep_output == NULL) {
        perror("Erreur lors de l'exécution de pgrep");
        return;
    }

    // Ajouter les PIDs au cgroup
    char *pid_str= malloc(1024*sizeof(char));
    while (fgets(pid_str, 1024*sizeof(char), pgrep_output) != NULL) {
        int pid = atoi(pid_str);
        if (pid <= 0) {
            fprintf(stderr, "PID invalide : %d\n", pid);
            continue;
        }

        char *pid_cgroup_path=  malloc(1024*sizeof(char));
        snprintf(pid_cgroup_path, 1024*sizeof(char), "%s/cgroup.procs", cgroup_path);
        file = fopen(pid_cgroup_path, "w");
        if (file == NULL) {
            perror("Erreur lors de l'ouverture de cgroup.procs");
            pclose(pgrep_output);
            return;
        }
        fprintf(file, "%d\n", pid);
        fclose(file);

        free(pid_cgroup_path);
    }

    pclose(pgrep_output);

    // Afficher les détails
    printf("Mémoire totale = %ld Ko, Limite de mémoire = %ld Ko, Pourcentage de mémoire = %.2f%%, Pourcentage CPU = %.2f%%\n",
           total_memory / 1024, memory_limit / 1024, memory_percentage, cpu_percentage);

    free(cgroup_path);
    free(cpu_max_path);
    free(memory_max_path);
    free(pgrep_cmd);
    free(pid_str);


}

// Affiche les informations des processus du cgroup avec top
void display_cgroup_info(char *cgroup_name) {

    size_t cgroup_path_size = strlen(CGROUP_BASE) + strlen(cgroup_name) + strlen("/cgroup.procs") + 1;
    char *cgroup_path = malloc(cgroup_path_size * sizeof(char));

    snprintf(cgroup_path, cgroup_path_size, "%s%s/cgroup.procs", CGROUP_BASE, cgroup_name);

    // Ouvrir le fichier contenant les PIDs
    FILE *cgroup_file = fopen(cgroup_path, "r");
    if (cgroup_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier cgroup.procs");
        free(cgroup_path);
        return;
    }

    size_t top_cmd_size = 1024;
    char *top_cmd = malloc(top_cmd_size * sizeof(char));

    strcpy(top_cmd, "top -p ");

    size_t pid_str_size = 1024;
    char *pid_str = malloc(pid_str_size * sizeof(char));

    int first_pid = 1; // Indicateur pour le premier PID

    while (fgets(pid_str, pid_str_size, cgroup_file) != NULL) {
        strtok(pid_str, "\n");  // Enlever le caractère de nouvelle ligne de pid_str

        if (!first_pid) {
            strcat(top_cmd, ",");
        }
        first_pid = 0;

        // Agrandir top_cmd si nécessaire
        size_t needed_size = strlen(top_cmd) + strlen(pid_str) + 2;
        if (needed_size > top_cmd_size) {
            top_cmd_size = needed_size;
            char *new_top_cmd = realloc(top_cmd, top_cmd_size * sizeof(char));
            if (new_top_cmd == NULL) {
                perror("Erreur de réallocation mémoire pour top_cmd");
                free(top_cmd);
                free(pid_str);
                fclose(cgroup_file);
                free(cgroup_path);
                return;
            }
            top_cmd = new_top_cmd;
        }

        strcat(top_cmd, pid_str);
    }

    fclose(cgroup_file);

    // Exécution de la commande top
    if (system(top_cmd) == -1) {
        perror("Erreur lors de l'exécution de la commande top");
    }

    free(top_cmd);
    free(pid_str);
    free(cgroup_path);
}
