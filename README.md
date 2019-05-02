# SpaceShooter

## Dépendances
- Cmake
- MinGW

## Installation
```
set "PATH=%PATH%;C:\Program Files (x86)\CodeBlocks\MinGW\bin;"
mkdir build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_SH=CMAKE_SH-NOTFOUND -G "CodeBlocks - MinGW Makefiles" ..
mingw32-make
```