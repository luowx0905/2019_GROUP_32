cmake_minimum_required(VERSION 3.12.0)

project(Model_Loading_Library VERSION 0.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #Makes sure compiler knows to use c++111
include (CTest)
#adds all the classes as libraries
add_library(cell src/cell.cpp include/cell.h)
add_library(material src/material.cpp include/material.h)
add_library(matrix src/matrix.cpp include/matrix.h)
add_library(vector src/vector.cpp include/vector.h)
add_library(model src/model.cpp include/model.h)
add_library(hexa src/hexahedron.cpp include/hexahedron.h)
add_library(pyramid src/pyramid.cpp include/pyramid.h)
add_library(tetra src/tetrahedron.cpp include/tetrahedron.h)
include_directories(include)
#identify mains of executables
add_executable(modelTest test/modelTestMain.cpp)
add_executable(matrixTest test/matrixTestMain.cpp)
add_executable(vectorTest test/autoTest1.cpp)
#test main includes
target_include_directories(modelTest PUBLIC include)
target_include_directories(matrixTest PUBLIC include)
#links required libraries
target_link_libraries(modelTest model cell material matrix vector hexa pyramid tetra)
target_link_libraries(matrixTest matrix vector)
target_link_libraries(vectorTest vector)

add_test(vectorTest vectorTest)
