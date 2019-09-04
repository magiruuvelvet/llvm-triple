CreateTarget(${PROJECT_NAME} EXECUTABLE ${PROJECT_NAME} 17)

find_package(LLVM REQUIRED)

message(STATUS "Found LLVM version: ${LLVM_VERSION}")
message(STATUS "Found LLVM directory: ${LLVM_DIR}")
message(STATUS "Found LLVM headers: ${LLVM_INCLUDE_DIRS}")

llvm_map_components_to_libnames(llvm_libs support)

target_include_directories(${PROJECT_NAME} PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${LLVM_DEFINITIONS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${llvm_libs})
