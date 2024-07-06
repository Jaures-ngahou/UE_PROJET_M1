#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cgroup_limit.h"

int is_valid_percentage(float percentage) {
    return percentage >= 0.0 && percentage <= 100.0;
}

int main() {
    int choice;
    char *program_name = malloc(256 * sizeof(char));
    char *cgroup_name = malloc(256 * sizeof(char));
    float cpu_percentage;
    float memory_percentage;

    if (program_name == NULL || cgroup_name == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        return EXIT_FAILURE;
    }

    do {
        printf("\n==================== Menu ====================\n");
        printf("1. Définir un cgroup et appliquer les limites\n");
        printf("2. Afficher les informations des processus du cgroup\n");
        printf("0. Quitter\n");
        printf("==============================================\n");
        printf("Choisissez une option: ");

        while (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // vider le buffer d'entrée
            printf("Entrée invalide. Veuillez entrer un nombre: ");
        }

        switch (choice) {
            case 1:
                printf("Entrez le nom du programme: ");
                scanf("%255s", program_name);

                printf("Entrez le pourcentage de CPU (0-100): ");
                while (scanf("%f", &cpu_percentage) != 1 || !is_valid_percentage(cpu_percentage)) {
                    while (getchar() != '\n'); // vider le buffer d'entrée
                    printf("Pourcentage invalide. Veuillez entrer un nombre entre 0 et 100: ");
                }

                printf("Entrez le pourcentage de mémoire (0-100): ");
                while (scanf("%f", &memory_percentage) != 1 || !is_valid_percentage(memory_percentage)) {
                    while (getchar() != '\n'); // vider le buffer d'entrée
                    printf("Pourcentage invalide. Veuillez entrer un nombre entre 0 et 100: ");
                }

                create_cgroup_and_apply_limits(program_name, cpu_percentage, memory_percentage);
                break;

            case 2:
                printf("Entrez le nom du cgroup: ");
                scanf("%255s", cgroup_name);
                display_cgroup_info(cgroup_name);
                break;

            case 0:
                printf("Quitter le programme.\n");
                break;

            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    } while (choice != 0);

    free(program_name);
    free(cgroup_name);

    return EXIT_SUCCESS;
}

