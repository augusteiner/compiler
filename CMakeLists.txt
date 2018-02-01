
cmake_minimum_required(VERSION 3.2)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

set(K_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

flex_target(lexer kaleidoscope.ll "${K_BINARY_DIR}/kaleidoscope.ll.cpp"
        DEFINES_FILE "${K_BINARY_DIR}/kaleidoscope.ll.hpp")

bison_target(parser kaleidoscope.yy "${K_BINARY_DIR}/kaleidoscope.yy.cpp")

add_flex_bison_dependency(lexer parser)

include_directories("${CMAKE_SOURCE_DIR}" "${K_BINARY_DIR}")

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

llvm_map_components_to_libnames(LLVM_LIBRARIES support core irreader mcjit native)

add_executable(
    main
    main.cpp
    driver.cpp
    ast.cpp
    ${FLEX_lexer_OUTPUTS}
    ${BISON_parser_OUTPUTS}
)

target_link_libraries(main ${LLVM_LIBRARIES})
