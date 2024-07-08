#               PROJET: INF42228
----
## THÈME: RÉGULATION DU POURCENTAGE D’UTILISATION DES     RESSOURCES (CPU, RAM) PAR UN PROGRAMME DANS UN ORDINATEUR
 
----

**GROUPE 2**



| Noms et Prénoms | Matricules |
| -------- | -------- |
|MEBENGA MBALLA JEAN    |  20U2782|
|KENFACK NGAHOU JAURES	 | 20U2883|
|BANGANDO SEBATIEN ISMAEL | 14B2631|

----
### Etape 1: Prérequis

- [x] Avoir un ordinateur
- [x] Avoir un OS Linux( Debian, Ubuntu)
- [x] OS avec Gcc gcc, make, cgroup2 installé et fonctionnels
        - Si non installer ses outils avec la commande: ```sudo apt install gcc make cgroup-tools ```
- [x] Avoir git et github installé configurés

----
### Etape 2: Téléchargement du code sources

Le téléchargement du code source peut se faire soit directement avec ```git clone``` soit en téléchargeant l'archive ```.zip``` contenant le code source.

- [x] Soit avec``` git clone```:
-  Ouvrir le terminal exécutée cette commande: 
        -  ```git clone https://github.com/Jaures-ngahou/UE_PROJET_M1.git```

- [x] Soit en téléchargeant L'archive ```.zip```:
- lien de téléchargement de l'archive: 
    - https://github.com/Jaures-ngahou/UE_PROJET_M1/archive/refs/heads/main.zip
- se positionner dans le dossier qui a reçu l'archive et Ouvrer le termimal et désarchiver le code source:
    - ```unzip UE_PROJET_M1-main.zip -d UE_PROJET_M1```
----
### Directory layout:
    UE_PROJET_M1/
        ProjetM1/
            cgroup_limit.h : fichier d'entête pour la définition des focntions contenues dans le fichier cgroup_limit.c.
            cgroup_limit.c : fichier source qui contenant toutes limites
            main.c :  fichier principal
            Makefile: fichier qui contient les instruction pour compiler le code source
----
### Etape 3: Compilation du code source et éxecution
* **Pour compiler le code source:**
    1. ```cd UE_PROJET_M1/ProjetM1/```
    2. ```make```

* **Pour executer le programme:**
1. ```sudo ./manager```

![](https://s3.hedgedoc.org/demo/uploads/9f674b79-753d-4d64-b163-8819bff025a1.png)

2. Pour definir les limites(cpu et ram) d'un programme:
    

```
    Choisissez une option: 1
    Entrez le nom du programme: nom_programme
    Entrez le pourcentage de CPU (0-100): pourcentage maximal de cpu alloué au programme
    Entrez le pourcentage de mémoire (0-100):  pourcentage maximal de la RAM alloué au programme
```
![](https://s3.hedgedoc.org/demo/uploads/651fa800-06dd-421b-bdfa-f91b6167a0b4.png)


3. Pour afficher les informations des processus du cgroup

```
    Choisissez une option: 2
    Entrez le nom du cgroup: nom_programme
```
 ![](https://s3.hedgedoc.org/demo/uploads/ae1df897-db6d-4877-83d1-0e16afcb0118.png)
 
 ![](https://s3.hedgedoc.org/demo/uploads/3fa3d89b-0a12-4da6-9eea-9482960a8a2c.png)

* appuyer sur la touche ```q``` du clavier pour revenir au menu principal

4. Quitter le programme:
```
    Choisissez une option: 0
```
![](https://s3.hedgedoc.org/demo/uploads/882f2f0e-a42b-4087-ae50-6a5696a8d04d.png)

----


### Vérification dans les fichiers du Cgroup2 

* Pour visualiser le fichier contenant la taille maximale de la ram allouée au programme: 
```
    cat /sys/fs/cgroup/nom_cgroup_crée/memory.max
```
* Pour visualiser le fichier contenant la taille actuelle de la ram allouée au programme: 
```
	cat /sys/fs/cgroup/nom_cgroup_crée/memory.current
```
* Pour visualiser le fichier contenant le pourcentage maximal de cpu alloué au programme: 
```
	cat /sys/fs/cgroup/nom_cgroup_crée/cpu.max
	ou
	ps -aux | awk 'NR==1 || /nom_programme/'
```
![](https://s3.hedgedoc.org/demo/uploads/c6f2607e-7d2f-4a69-83ee-551ea7d211c6.png)

----
