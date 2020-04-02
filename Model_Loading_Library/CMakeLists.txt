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
add_executable(modelTest test/modelTest.cpp)
add_executable(matrixTest test/matrixTest.cpp)
add_executable(vectorTest test/vectorTest.cpp)

#links required libraries
target_link_libraries(modelTest model cell material matrix vector hexa pyramid tetra)
target_link_libraries(matrixTest matrix vector)
target_link_libraries(vectorTest vector)

add_test(vectorTest vectorTest)
add_test(matrixTest matrixTest)
add_test(modelTest modelTest)

#Copies the testfiles into the binary directory.
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	FILE(COPY test/ExampleModel1.mod DESTINATION "${CMAKE_BINARY_DIR}/Debug")
	FILE(COPY test/ExampleModel2.mod DESTINATION "${CMAKE_BINARY_DIR}/Debug")
	FILE(COPY test/ExampleModel3.mod DESTINATION "${CMAKE_BINARY_DIR}/Debug")
else ()
	FILE(COPY test/ExampleModel1.mod DESTINATION "${CMAKE_BINARY_DIR}")
	FILE(COPY test/ExampleModel2.mod DESTINATION "${CMAKE_BINARY_DIR}")
	FILE(COPY test/ExampleModel3.mod DESTINATION "${CMAKE_BINARY_DIR}")
endif ()