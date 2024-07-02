#include "programm.h"


int cgroup_exists(const char *path) {
    return access(path, F_OK) != -1;
}
void remove_cgroup(const char *path) {
    if (cgroup_exists(path)) {
        if (rmdir(path) != 0) {
            perror("Error removing cgroup");
        } else {
            printf("Cgroup %s removed.\n", path);
        }
    }
}

void create_cgroup(char *program_name, int cpu_percentage, long memory_limit) {
    char cgroup_path[MAX_PATH_LEN];
    FILE *file;

    // Construction du chemin complet du cgroup
    snprintf(cgroup_path, sizeof(cgroup_path), "%s%s/", CGROUP_BASE, program_name);
 remove_cgroup(cgroup_path);
    // Création du cgroup
    if (mkdir(cgroup_path, 0755) != 0) {
        perror("Error creating cgroup");
        return;
    }

    // Définition du pourcentage de CPU
    char cpu_max_path[MAX_PATH_LEN];
    snprintf(cpu_max_path, sizeof(cpu_max_path), "%s%s/cpu.max", CGROUP_BASE, program_name);
    file = fopen(cpu_max_path, "w");
    if (file == NULL) {
        perror("Error opening cpu.max");
        return;
    }
    printf("cpu max:%d000",cpu_percentage);
    fprintf(file, "%d000", cpu_percentage); // Convertir en µs (1000 pour 1%)
    fclose(file);

    // Définition de la limite de mémoire
    char memory_max_path[MAX_PATH_LEN];
    snprintf(memory_max_path, sizeof(memory_max_path), "%s%s/memory.max", CGROUP_BASE, program_name);
    file = fopen(memory_max_path, "w");
    if (file == NULL) {
        perror("Error opening memory.max");
        return;
    }
    printf("ram maximale:%ld",memory_limit);
        fprintf(file, "%ld", memory_limit);
    fclose(file);

    // Récupération des PIDs du programme
    char pgrep_cmd[MAX_PATH_LEN];
    snprintf(pgrep_cmd, sizeof(pgrep_cmd), "pgrep %s", program_name);

    // Exécution de la commande pgrep pour obtenir les PIDs
    FILE *pgrep_output = popen(pgrep_cmd, "r");
    if (pgrep_output == NULL) {
        perror("Error running pgrep");
        return;
    }

    // Lecture des PIDs et insertion dans le cgroup
    char pid_str[MAX_PATH_LEN];
    while (fgets(pid_str, sizeof(pid_str), pgrep_output) != NULL) {
        int pid = atoi(pid_str);
        char pid_cgroup_path[500];
        snprintf(pid_cgroup_path, sizeof(pid_cgroup_path), "%s/cgroup.procs", cgroup_path);
        file = fopen(pid_cgroup_path, "w");
        if (file == NULL) {
            perror("Error opening cgroup.procs");
            pclose(pgrep_output);
            return;
        }
        fprintf(file, "%d\n", pid);
        fclose(file);
    }

    pclose(pgrep_output);
}


long get_total_ram() {
    FILE *file = fopen("/proc/meminfo", "r");
    if (!file) {
        perror("Failed to open /proc/meminfo");
        exit(EXIT_FAILURE);
    }

    long total_ram_kb = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "MemTotal: %ld kB", &total_ram_kb) == 1) {
            break;
        }
    }

    fclose(file);

    if (total_ram_kb == 0) {
        fprintf(stderr, "Failed to read total RAM from /proc/meminfo\n");
        exit(EXIT_FAILURE);
    }

    // Convert total RAM from kilobytes to bytes
    long total_ram_bytes = total_ram_kb * 1024;

    return total_ram_bytes;
}

long calculate_ram_size(int percentage) {
    if (percentage < 0 || percentage > 100) {
        fprintf(stderr, "Invalid percentage: %d\n", percentage);
        exit(EXIT_FAILURE);
    }

    long total_ram = get_total_ram();
    long size = total_ram * percentage / 100;

    return size;
}

