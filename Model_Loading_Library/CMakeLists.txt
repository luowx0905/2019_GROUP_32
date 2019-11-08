cmake_minimum_required(VERSION 3.16.0)

project(Model_Loading_Library VERSION 0.1)

add_library(cell src/cell.cpp include/cell.h)
add_library(material src/material.cpp include/material.h)
add_library(matrix src/matrix.cpp include/matrix.h)
add_library(model src/model.cpp include/model.h)
add_library(vector src/vector.cpp include/vector.h)
target_include_directories(vector PUBLIC include)
add_executable(testmain test/main.cpp)
target_include_directories(testmain PUBLIC include)
target_link_libraries(testmain cell material matrix model vector)