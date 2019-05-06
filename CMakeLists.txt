cmake_minimum_required(VERSION 3.6)
project(Run)

# Définit le dossier de sortie
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Definit le dossier des libraries et des include
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

# Link tous les fichiers
set(SOURCE_FILES src/main.c src/game.c src/body.c src/world.c include/world.h)
add_executable(Run ${SOURCE_FILES})

# Link les DLL
target_link_libraries(Run mingw32 SDL2main SDL2 SDL2_ttf SDL2_image)