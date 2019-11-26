# Model Loading Library
## Test Setup
**1. Navigate to build directory**  
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
