cmake_minimum_required(VERSION 3.14)
project(asd20192020tpg6 C)

set(CMAKE_C_STANDARD 11)

add_executable(FGKtest fileManager.c decoding.c encoding.c bufferManager.c FGK.c tree.c)
add_executable(FGKWorking fgkWorking.c)
