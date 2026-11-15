find_package(GTest REQUIRED)

macro(bimg_test name)
    set(NAME "${CATEGORY}_${name}")
    add_executable(${NAME} ${name}.cpp)
    target_link_libraries(${NAME} PRIVATE bimg GTest::gtest_main)
    add_test(NAME ${NAME} COMMAND ${NAME})
endmacro()


add_subdirectory(core)
add_subdirectory(io)
add_subdirectory(labeling)