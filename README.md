
# Run !
  
## Introduction  
  
Le projet à été codé à sur l'IDE JetBrains CLion avec MinGw et CMake. **Une version du projet en CodeBlocks est disponible dans le dossier codeblocks/**
  
## Structure du projet  
 
 ```
├───assets/ : Images et polices  
├───cmake-build-debug : Build crée par CMake  
├───codeblocks/ : Projet sous code blocks
├───include/ : Tous les fichiers .h
├───lib/ : Tous les fichiers .lib
├───output/ : Tous les fichiers .dll plus l'executable
├───src/ : Tous les fichiers sources en .c
├───CMakeLists.txt: Fichier de configuration de CMake  
├───synchro-codeblocks.bat : Executer ce fichier replique les fichiers sources du projet CLion vers Codeblocks 
```
  
  
## Dépendances  
- [CMake](https://cmake.org)  
- [MinGW](http://www.mingw.org/)  
  
## Installation  

### Avec CLion
Ajouter MinGW en Toolchains. Attention, si Git est présent dans la variable PATH de l'ordinateur, ajouter en argument de CMake (Settings > Build > CMake) l'argument `-DCMAKE_SH=CMAKE_SH-NOTFOUND`
```  
set "PATH=%PATH%;[CheminVersMinGW]\MinGW\bin;"  
mkdir build  
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_SH=CMAKE_SH-NOTFOUND -G "CodeBlocks - MinGW Makefiles" ..  
mingw32-make  

```
![Capture](https://raw.githubusercontent.com/ThomasLachaux/Run/master/assets/rules.png)