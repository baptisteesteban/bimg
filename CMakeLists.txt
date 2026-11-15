cmake_minimum_required(VERSION 3.24)
project(Bimg C CXX)

include(CheckIncludeFileCXX)

option(ENABLE_TESTS "Build the test suite" OFF)
option(ENABLE_BENCHMARKS "Build the benchmark suite" OFF)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

check_include_file_cxx("print" have_include_print)
if (NOT have_include_print)
    message(ERROR "Compiler must support <print> include.")
endif (NOT have_include_print)

add_library(stb_image OBJECT src/io/stb_image.c)

add_library(bimg)
target_sources(bimg PRIVATE
    src/io/imread.cpp
    src/io/imwrite.cpp
)
target_include_directories(bimg PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(bimg PRIVATE stb_image)

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif (ENABLE_TESTS)

if (ENABLE_BENCHMARKS)
    add_subdirectory(benchmarks)
endif (ENABLE_BENCHMARKS)