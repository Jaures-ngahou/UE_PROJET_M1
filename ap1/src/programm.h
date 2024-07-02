#ifndef PROGRAMM_H
#define PROGRAMM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define CGROUP_BASE "/sys/fs/cgroup/"
#define MAX_PATH_LEN 256

int cgroup_exists(const char *path) ; //verifier si le cgroup se trouve deja dans /sys/fs/cgroup/
void remove_cgroup(const char *path) ; // supprimer le cgroup s'il existe deja

void create_cgroup(char *program_name, int cpu_percentage, long memory_limit) ; // creer le groupe
long get_total_ram(); // retourne la capacité de la ram de la machine
long calculate_ram_size(int percentage); //determine la taille de la memoire correspondant à au pourcentage passé en parametre





#endif