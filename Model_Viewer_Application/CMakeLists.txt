cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

PROJECT( ModelViewerApp )

# The CMake build process might generate some new files in the current
# directory. This makes sure they can be found.
set( CMAKE_INCLUDE_CURRENT_DIR ON )




# This allows CMake to run one of Qt's build tools called moc
# if it is needed. moc.exe can be found in Qt's bin directory.
# We'll look at what moc does later.
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

# Find the Qt widgets package. This locates the relevant include and
# lib directories, and the necessary static libraries for linking.
find_package( Qt5Widgets )

set( UIS mainwindow.ui )
qt5_wrap_ui( UI_Srcs ${UIS} )

# Also link to VTK
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )



# Create a container for all library sources TODO change this so instead it links with .lib files made by CMakeLists.txt in library directory
set( INCLUDE_DIR ../Model_Loading_Library/include )
set( SRC_DIR ../Model_Loading_Library/src )
add_library( MODEL_LOADING_LIBRARY ${SRC_DIR}/model.cpp ${SRC_DIR}/cell.cpp ${SRC_DIR}/material.cpp ${SRC_DIR}/vector.cpp ${SRC_DIR}/hexahedron.cpp
${SRC_DIR}/tetrahedron.cpp ${SRC_DIR}/pyramid.cpp ) 

include_directories( ${INCLUDE_DIR} )
# target_link_libraries(MODEL_LOADING_LIBRARY ${INCLUDE_DIR} )

# Define the executable output and its sources
add_executable( ModelViewerApp MACOSX_BUNDLE
		main.cpp mainwindow.cpp 
		mainwindow.h 
		dialogcolor.h dialogcolor.cpp
		mainwindow.ui
		${MODEL_LOADING_LIBRARY}
		${UI_Srcs}
		${QRC_Srcs}
		)

target_link_libraries( ModelViewerApp MODEL_LOADING_LIBRARY )

# Tell CMake that the executable depends on the Qt::Widget libraries.
target_link_libraries( ModelViewerApp Qt5::Widgets )

# Tell CMake that the executable depends on the VTK libraries
target_link_libraries( ModelViewerApp ${VTK_LIBRARIES} )

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	FILE(COPY Resources/splashscreen.png DESTINATION "${CMAKE_BINARY_DIR}/Debug")
else ()
	FILE(COPY Resources/splashscreen.png DESTINATION "${CMAKE_BINARY_DIR}")
endif ()