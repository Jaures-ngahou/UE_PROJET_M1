#include "programm.h"


int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <cpu_percentage> <memory_limit> <program_name>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int i;
    int cpu_percentage = atoi(argv[1]);
    long percentage = atol(argv[2]);
    char *program_name = argv[3];
    long memory_limit = calculate_ram_size(percentage);
    printf("nom du programme: %s \n ",program_name);
    printf("limite  max du cpu: %d%% \n ",cpu_percentage);
    printf("limite max de la ram %ld%%  soit : %ld Mo\n\n", percentage, memory_limit/(1024*1024));
    printf("ces informations sont elles correctes: \n 1 pour oui \n 2 pour non\n  ");
    scanf("%d", &i);
    if(i!=1){
        printf("annulation\n");
        return 0;
    }


    create_cgroup(program_name, cpu_percentage, memory_limit);

    return EXIT_SUCCESS;
}
