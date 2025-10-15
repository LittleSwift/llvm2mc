file(GLOB_RECURSE SRC_FILES "*.cpp" "*.h")

message(${SRC_FILES})

add_executable(llvm2mc ${SRC_FILES})
find_package(LLVM REQUIRED CONFIG)
target_include_directories(llvm2mc PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(llvm2mc PRIVATE LLVMCore LLVMBitReader LLVMIRReader)
find_package(OpenSSL REQUIRED)
target_include_directories(llvm2mc PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(llvm2mc PRIVATE ${OPENSSL_LIBRARIES})

install(TARGETS llvm2mc
        RUNTIME DESTINATION bin
)