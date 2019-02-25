cmake_minimum_required(VERSION 3.6)
project(SpaceShooter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(SOURCE_FILES src/main.c src/game.c src/body.c src/world.c include/world.h)
#set(SOURCE_FILES src/testing.c)
add_executable(SpaceShooter ${SOURCE_FILES})

target_link_libraries(SpaceShooter mingw32 SDL2main SDL2)