# News  
- **Please remember to make pull requests from master regularly**
- **Comment your code!!!!** 
- **Add any jobs to the job list that you notice need doing but you cannot complete immediately!**

# Job list

|Jobs|Status|Initials|Notes|
|----|------|--------|-----|
|Change CMakeLists.txt so that library does not need to be in the same directory as application, possibly add a top level CMakeLists.txt|NS|||
|Change format of UI such that it can be resized|NS|||
|Fix compile issues from sem1 feedback|NS||Ask Paul what these were|
|Change CMakeLists.txt to include library|U|EDS|Will need to be looked at if more CMakeLists added|
|Complete camera reset method so that both the camera's position and orientation are reset|C|EDS||
|Change name of vtkWindow from openGLWidget to something more accurate|NS|||
|Implement a orientation widget|C|EDS|Widget accessible through view menu|
|Implement a box widget|C|EDS|Widget works but there are some issues when a new model is loaded|
|Fix box widget issues when loading new model|NS|||
|Refactor code and remove fluff - generally just neaten up code|NS|||
|Condense Open functions into one that can handle both .mod and .stl|C|EDS||
|Fix compile warnings - mostly type changes|NS|||
|Create a function in mainwindow.cpp that resets all widgets to a default state e.g. whether they're checked, enabled etc...|NS|||
|Write unit tests for each class in library|NS||These tests will be automated and so must return 0 if test succeeded - see vectorTest.cpp as an example|
|Finish Doxygen documentation of library files|NS|||
|Automate documentation upload using travis|C|EDS||
|Automate testing using travis|C|EDS|Be sure to add a badge to the readme showing the status of the most recent build|
|Add install code to CMakeLists.txt --> must also package required vtk and qt dlls|NS|||
|Make a better splash screen|NS|||
|Change the name that displays at the top left of the qt application from mainwindow to something more reflective of the program (Model Viewer perhaps?)|NS|||
|Make filter controls pop up in a separate dialog box|NS|||
|Make camera reset function ensure that object is centered nicely|NS|||
|Remove un-needed buttons and their functions |NS||i.e 'red->blue->red'|
|Add a panel which displays information about the model|U|EDS|Currently displays number of cells and points could add more stats yet|
|Find or create icons of a (fairly) consistent theme to use for actions on the toolbar|NS||E.g. Open, Save Screenshot, display orientation widget, help etc.|

## Status Legend
- **C** - Completed  
- **U** - Underway  
- **NS** - Not Started  
