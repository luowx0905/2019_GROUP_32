// this file contains the defination of class MainWindow

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <vector>

#include <vtkSmartPointer.h>
#include <vtkSTLReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>

#include <vtkAxesActor.h>
#include <vtkBoxWidget2.h>
#include <vtkBoxRepresentation.h>
#include <vtkCamera.h>
#include <vtkCommand.h>
#include <vtkCellArray.h>
#include <vtkClipDataSet.h>

#include <vtkDataSetMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkLight.h>
#include <vtkNamedColors.h>

#include <vtkNew.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkPlane.h>
#include <vtkPlaneWidget.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkPyramid.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSTLReader.h>
#include <vtkShrinkFilter.h>
#include <vtkSmartPointer.h>
#include <vtkTetra.h>
#include <vtkTransform.h>
#include <vtkUnstructuredGrid.h>


using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class vtkBoxWidgetCallback : public vtkCommand
{
public:
  static vtkBoxWidgetCallback *New();
  void SetActor( vtkSmartPointer<vtkActor> actor );
  virtual void Execute( vtkObject *caller, unsigned long, void* );
  vtkSmartPointer<vtkActor> m_actor;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    // open the STL file
    void open();
    // set the color of the light
    void setLightColor();
    // set the intensity of the light
    void setLightIntensitySpinBox();
    void setLightIntensitySlider();
    // reset the light
    void resetLight();
    // change the color of the object in a specfic sequence
    void changModelColorItor();
    // chang color of the object to a user selected color
    void selectedObjectColor();
    // set the edge visibility
    void visableEdge(int);
    // set background color
    void setBackgroundColor();
    // apply filter setting
    void applyFilter(int);
    // add primitive shape
    void primitiveShape(int);
    // reset camera
    void resetCamera();

    // open the mod file
    void openMODFile();

    //adds orientation widget to the bottom left of the screen
    void displayOrientationWidget(bool);
    //adds widget that allows planes to be edited
    void displayPlaneWidget(bool);
    //adds box widget that allows model to be edited
    void displayBoxWidget(bool);

private:
    Ui::MainWindow *ui;

    vtkSmartPointer<vtkSTLReader> STLReader;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkActor> actor;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkLight> light;
	vtkSmartPointer<vtkNamedColors> color;
    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkActor> shapeActor;
    vtkSmartPointer<vtkCamera> camera;
    vtkSmartPointer<vtkAxesActor> axes;
    vtkSmartPointer<vtkOrientationMarkerWidget> orientationMarker;
    vtkSmartPointer<vtkPlaneWidget> planeWidget;
    vtkSmartPointer<vtkBoxWidget2> boxWidget;
    vtkSmartPointer<vtkBoxWidgetCallback> boxWidgetCallback;

    vector<double> value; // store the RGB value of light
    double intensity; // store the intensity of light
    vector<vtkSmartPointer<vtkActor>> primitiveShapeActor; // store all the actor for primitive shape
    vector<vtkSmartPointer<vtkActor>>::const_iterator shapeItor; // iterator for primitive shape
};
#endif // MAINWINDOW_H
