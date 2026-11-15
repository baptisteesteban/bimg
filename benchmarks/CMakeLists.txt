find_package(benchmark REQUIRED)

macro(bimg_benchmark name)
    add_executable(benchmark_${name} ${name}.cpp)
    target_link_libraries(benchmark_${name} PRIVATE benchmark::benchmark_main bimg)
endmacro(bimg_benchmark)

bimg_benchmark(connected_components)