cmake_minimum_required(VERSION 3.7)
project(mafn_kernel)

file(GLOB_RECURSE SOURCE_FILES
        "src/*.h"
        "src/*.c"
        "src/*.s"
        )


add_executable(mafn_kernel ${SOURCE_FILES})