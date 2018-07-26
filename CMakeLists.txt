cmake_minimum_required(VERSION 3.10)
project(fate C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -lm)

add_executable(fate main.c util.c util.h earth.c earth.h tle.c tle.h sgp.c sgp.h vec.c vec.h)