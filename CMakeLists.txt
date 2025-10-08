cmake_minimum_required(VERSION 4.0)
project(llvm2mc)

set(CMAKE_CXX_STANDARD 20)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM include dirs: ${LLVM_INCLUDE_DIRS}")

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.h)

add_executable(llvm2mc ${SRC_FILES})
find_package(LLVM REQUIRED CONFIG)
target_include_directories(llvm2mc PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(llvm2mc PRIVATE LLVMCore LLVMBitReader LLVMIRReader)
find_package(OpenSSL REQUIRED)
target_include_directories(llvm2mc PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(llvm2mc PRIVATE ${OPENSSL_LIBRARIES})


file(GLOB_RECURSE HEADER_FILES include/*.h)
add_library(headers INTERFACE ${HEADER_FILES})

install(TARGETS llvm2mc
        RUNTIME DESTINATION bin
)

install(DIRECTORY include/
        DESTINATION include/llvm2mc
        FILES_MATCHING PATTERN "*.h"
)
