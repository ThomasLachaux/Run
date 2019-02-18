cmake_minimum_required(VERSION 3.13)
project(SpaceShooter C)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_C_STANDARD 99)

add_executable(SpaceShooter main.c)

target_link_libraries(SpaceShooter mingw32 SDL2main SDL2)