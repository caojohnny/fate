cmake_minimum_required(VERSION 3.10)
project(fate C)

set(CMAKE_C_STANDARD 99)

add_executable(fate
        main.c
        util.c util.h
        tle.c tle.h
        sgp.c sgp.h
        vec.c vec.h
        eci.c eci.h
        astrotime.c astrotime.h)
target_link_libraries(fate m)