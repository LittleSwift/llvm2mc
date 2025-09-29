cmake_minimum_required(VERSION 4.0)
project(llvm2mc)

set(CMAKE_CXX_STANDARD 20)

set(LLVM_DIR "/opt/homebrew/opt/llvm/lib/cmake/llvm")
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM include dirs: ${LLVM_INCLUDE_DIRS}")

add_executable(llvm2mc main.cpp
        stringUtils.h
        instructions/alloca.h
        instructions/br.h
        predefined/abort.h
        const.h
        constConversion.h
        instructions/ret.h
        instructions/binaryOperator.h
)
target_include_directories(llvm2mc PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(llvm2mc PRIVATE LLVMCore LLVMBitReader LLVMIRReader)

install(TARGETS llvm2mc
        RUNTIME DESTINATION bin
)

install(DIRECTORY include/
        DESTINATION include/llvm2mc
        FILES_MATCHING PATTERN "*.h"
)
