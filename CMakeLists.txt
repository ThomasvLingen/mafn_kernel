cmake_minimum_required(VERSION 3.7)
project(mafn_kernel)

set(CMAKE_SYSTEM_NAME custom)
set(triple i686-elf)

include_directories(src/kernel/include)
include_directories(src/libc/include)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)


file(GLOB_RECURSE SOURCE_FILES
        "src/*.h"
        "src/*.c"
        "src/*.s"
        )


add_executable(mafn_kernel ${SOURCE_FILES})