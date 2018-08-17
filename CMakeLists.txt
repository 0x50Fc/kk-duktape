

cmake_minimum_required(VERSION 3.4.1)

add_library(duktape
            STATIC
            lib/duktape/src/duktap.c
            )

include_directories(
            ./include
            )
