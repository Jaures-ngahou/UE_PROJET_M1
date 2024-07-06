#ifndef CGROUP_LIMIT_H
#define CGROUP_LIMIT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>

#define CGROUP_BASE "/sys/fs/cgroup/"

// Fonction pour créer un cgroup et appliquer les limites(%CPU, %RAM)
void create_cgroup_and_apply_limits(char *program_name, float cpu_percentage, float memory_percentage);

// Fonction pour afficher les informations des processus du cgroup
void display_cgroup_info(char *cgroup_name);

#endif
