cmake_minimum_required(VERSION 4.0)
project(llvm2mc)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)


file(GLOB_RECURSE HEADER_FILES include/*.h)
add_library(headers INTERFACE ${HEADER_FILES})

install(DIRECTORY include/
        DESTINATION include/llvm2mc
        FILES_MATCHING PATTERN "*.h"
)
