UE_PROJET: INF42228 
#GROUPE 2


#Membres du GRROUPE :
MEBENGA MBALLA JEAN  	  20U2782
KENFACK NGAHOU JAURES	  20U2883
BANGANDO SEBATIEN ISMAEL  14B2631


========
# THÈME:RÉGULATION DU POURCENTAGE D’UTILISATION DES RESSOURCES (CPU, RAM) PAR UN PROGRAMME DANS UN ORDINATEUR

## SYSTÈME D'EXPLOITATION: lINUX (UBUNTU)


### TÉLÉCHARGEMENT DU PROJET DEPUIS GITHUB
```
	$ git clone https://github.com/Jaures-ngahou/UE_PROJET_M1.git
```
### Directory layout:
	ProjetM1/
		cgroup_limit.h : fichier d'en tete pour la définition des focntions contenues dans le fichier cgroup_limit.c.
		cgroup_limit.c : fichier source qui contenant toutes limites
		main.c :  fichier principal
		

## usage
Pour compiler notre programme:
```
	$ cd ProjetM1/
	$ sudo make
```

pour executer notre programme:
```
	$ sudo ./manager
	
```


Pour definir les limites d'un programme:
```
Choisissez une option: $1
Entrez le nom du programme: $nom_programme
Entrez le pourcentage de CPU (0-100): pourcentage maximal de cpu alloué au programme
Entrez le pourcentage de mémoire (0-100):  pourcentage maximal de la RAM alloué au programme

```

Pour afficher les informations des processus du cgroup
```
Choisissez une option: $2
Entrez le nom du cgroup: nom_programme

```

Pour visualiser le fichier contenant la taille maximale de la ram allouée au programme: 
```
	cat /sys/fs/cgroup/nom_programme/memory.max
```	

Pour visualiser le fichier contenant la taille actuelle de la ram allouée au programme: 
```
	cat /sys/fs/cgroup/nom_programme/memory.current
	
	
Pour visualiser le fichier contenant le pourcentage maximal de cpu alloué au programme: 
```
	cat /sys/fs/cgroup/nom_programme/cpu.max 
	ou
	ps -aux | awk 'NR==1 || /nom_programme/'

```	
	
	
	
	

