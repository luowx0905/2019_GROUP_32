cmake_minimum_required(3.16)

project(Model_Loading_Library VERSION 0.1)

add_library(cell src/cell.cpp)
add_library(material src/material.cpp)
add_library(matrix src/matrix.cpp)
add_library(model src/model.cpp)
add_library(vector src/vector.cpp)
target_include_directories(testmain include/)
add_executable(testmain test/main.cpp)
target_link_libraries(testmain cell material matrix model vector)