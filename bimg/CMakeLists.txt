add_library(stb_image OBJECT src/io/stb_image.c)

add_library(bimg)
target_sources(bimg PRIVATE
    src/io/imread.cpp
    src/io/imwrite.cpp
)
target_include_directories(bimg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(bimg PRIVATE stb_image)