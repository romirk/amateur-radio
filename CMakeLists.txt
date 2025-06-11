cmake_minimum_required(VERSION 3.31)
project(reframed C)

set(CMAKE_C_STANDARD 23)

include_directories(./include)

add_executable(reframed src/main.c
        src/ax25.c
        include/ax25.h)
