cmake_minimum_required(VERSION 3.29)
project(ARA C)

set(CMAKE_C_STANDARD 99)

add_executable(ARA main.c
        interface.c
        algorithms.c
        header.h
        net.c
        utils.c)
