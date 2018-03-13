
cmake_minimum_required(VERSION 3.4.1)

add_library(kk-duktape
            SHARED
            src/main/jni/kk-duktape.c
            src/main/jni/duktape/src/duktape.c
            src/main/jni/kk.c)

target_link_libraries(kk-duktape log)
