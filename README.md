# 3D Model Viewer Project
## Model Loading Application  
**CHECK JOB LIST IN NEWS.MD IF UNSURE OF WHAT TO DO**  
## Model Loading Library [![Build Status](https://travis-ci.com/EDrever-Smith/2019_GROUP_32.svg?token=KfjpPmpzoQSKxZtRyAzE&branch=master)](https://travis-ci.com/EDrever-Smith/2019_GROUP_32)  
**Documentation available at: https://edrever-smith.github.io/2019_GROUP_32/**
### Testing
#### Test Setup (Windows)
**1. Navigate to build directory**  
*Note: If this is the first time setup you will need to create the build folder using mkdir  
`cd Model_Loading_Library\build`  
**2. Generate cmake files in build directory**  
*Using mingw32:*`cmake -G "MinGW Makefiles" ..`  
*Using MSVC:*`cmake -G "Visual Studio 16 2019" ..`  
**3. Ensure compiler bins are in your PATH**  
*Using mingw32:*`set PATH=%PATH%;C:\your\directory\here`  
*Using MSVC:*`vcvarsall.bat [arch]`  
**4. Generate binaries using makefiles**  
*Using mingw32:*`mingw32-make`  
*Using MSVC:*`msbuild Model_Loading_Library.sln`  
**5. Run test.exes**  
*Using mingw32:*`testName.exe`  
*Using MSVC:*`Debug\testName.exe`  
--NOTE: it is important to run .exe while inside build directory or else test files will not be found  
#### Test Setup (Linux)
**1. Navigate to build directory**  
*Note: If this is the first time setup you will need to create the build folder using mkdir  
`cd Model_Loading_Library\build`  
**2. Generate cmake files in build directory**  
`cmake -G "Unix Makefiles" ..`  
**3. Generate binaries using makefiles**  
`make`  
**4. Run tests**  
`./testName`  
#### Test Files 
##### modelTest.exe  
Takes one argument which is a number between 1 and 3 that selects the test .mod file to be used. Outputs to the console details about all the details, cells and materials in the model and its center.  
Example Syntax:    
`modelTest.exe 2`   
##### matrixTest.exe    
Generates two randomly populated 3x3 matricies and performs a range of operations on them  
Example Syntax:  
`matrixTest.exe`

### Doxygen Setup
Ensure doxygen is installed on your system and is in your path. It can be downloaded from here: http://www.doxygen.nl/download.html   
**1. Navigate to root of Model_Loading_Library**  
`cd Model_Loading_Library`  
**2. Run doxygen**  
`doxygen`  
**3. Open index.html**  
*Windows:*`html/index.html`  
*Linux:*`[your browser] html/index.html`
