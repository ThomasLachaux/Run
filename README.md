


# Run !

## Pour jouer
Télécharger le projet en cliquant sur *Clone or Download > Dowload ZIP*.
L’exécutable se trouve dans le dossier *output/Run.exe*

## Introduction

Le projet à été codé à sur l'IDE JetBrains CLion avec MinGw et CMake avec la library SDL2. **Une version du projet en CodeBlocks est disponible dans le dossier codeblocks/**
## Structure du projet

 ```
├───assets/ : Images et polices
├───cmake-build-debug : Build crée par CMake
├───codeblocks/ : Projet sous code blocks
├───include/ : Tous les fichiers .h
├───lib/ : Tous les fichiers .lib
├───output/ : Tous les fichiers .dll plus l'executable
├───src/ : Tous les fichiers sources en .c
├───CMakeLists.txt: Fichier de configuration de CMake, précise à CMake où trouver les .dll, .h, .lib, .c...
├───synchro-codeblocks.bat : Executer ce fichier replique les fichiers sources du projet CLion vers Codeblocks
```

## Comment est organisé le code ?
Le code est organisé sous plusieurs fichiers de la façon linéaire suivante.
`main -> Game -> World -> Body`
Concrètement,
- Le main gère le Game
- Le Game gère le World
- Le World gère des Bodies

J'ai essayé (au mieux ^^) d'implémenter la Programmation Orienté Objet en tant que paradigme.

## Dépendances
- [CMake](https://cmake.org) *(Non nécessaire pour compiler avec Code::Blocks)*
- [MinGW](http://www.mingw.org/)

## Compilation

### Avec Code::Blocks
Avec pour ouvrir le projet avec codebloks, ouvrir le `.cpb` situé dans le dossier `codeblocks/`.

### Avec CLion
Ouvrir le projet avec CLion
Ouvrir les Settings > Build > Toolchains et ajouter MinGW en Toolchains.
Si Git est présent dans la variable PATH de l'ordinateur, écrire dans le champ Settings > Build > CMake > CMake Options la valeur `-DCMAKE_SH=CMAKE_SH-NOTFOUND`

### En ligne de commande

*MinGW et CMake soient installé et placé dans la variable `PATH` de l'ordinateur.*

#### Commandes pour créer le makefile
```
mkdir build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_SH=CMAKE_SH-NOTFOUND -G "CodeBlocks - MinGW Makefiles" ..
```
#### Commande pour compiler le projet
```
mingw32-make
```

![Capture](https://raw.githubusercontent.com/ThomasLachaux/Run/master/assets/rules.png)