cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")

set(CMAKE_BUILD_TYPE Debug)

project(Project LANGUAGES CXX)

#add_library(figure src/figure_array.cpp)

add_executable(main src/main.cpp)
#target_link_libraries(main figure)

set_target_properties(main PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON)

 add_subdirectory(
     "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
     "googletest"
 )
 add_executable(tests tests/test.cpp)

 set_target_properties(tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON)
 
 target_link_libraries(tests gtest gtest_main)
 enable_testing()