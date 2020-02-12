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
#include <vtkDataSetMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkLight.h>
#include <vtkNamedColors.h>

using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
    void setLightIntensity();
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

    vector<double> value; // store the RGB value of light
    double intensity; // store the intensity of light

};
#endif // MAINWINDOW_H
