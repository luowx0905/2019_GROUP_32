// this file contains the implementations of function defined in MainWindow class

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogcolor.h"

#include <map>
#include <vector>

#include <QFileDialog>
#include <QDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include <QButtonGroup>
#include <QMessageBox>

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSTLReader.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkNew.h>
#include <vtkLight.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkNamedColors.h>
#include <vtkPlane.h>
#include <vtkClipDataSet.h>
#include <vtkShrinkFilter.h>
#include <vtkPyramid.h>
#include <vtkTetra.h>
#include <vtkHexahedron.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>

#include "vector.h"
#include "model.h"
#include "material.h"
#include "cell.h"
#include "pyramid.h"
#include "hexahedron.h"
#include "tetrahedron.h"

using std::map;
using std::vector;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create a STL reader to read a STL file
    STLReader = vtkSmartPointer<vtkSTLReader>::New();
    // create a renderer
    renderer = vtkSmartPointer<vtkRenderer>::New();
    // create an actor used for set the properties of the model
    actor = vtkSmartPointer<vtkActor>::New();
    // create a light to provides light setting
    light = vtkSmartPointer<vtkLight>::New();
    // create color to set related information
	color = vtkSmartPointer<vtkNamedColors>::New();
    // create a mapper to hold a the information of the model
    mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    // create an actor for primitive shape
    shapeActor = vtkSmartPointer<vtkActor>::New();
    // create a camera
    camera = vtkSmartPointer<vtkCamera>::New();

    // set the background color of the render window
    renderer->SetBackground(0.1, 0.7, 0.1);
    // set the light
    light->SetLightTypeToHeadlight();
    light->SetPosition(5, 5, 15);
    light->SetPositional(true);
    light->SetConeAngle(10);
    light->SetFocalPoint(0, 0, 0);
    light->SetDiffuseColor(1, 1, 1);
    light->SetAmbientColor(1, 1, 1);
    light->SetSpecularColor(1, 1, 1);

    // link the render window to Qt widget
    ui->openGLWidget->SetRenderWindow(renderWindow);
	ui->openGLWidget->GetRenderWindow()->AddRenderer(renderer);

    // set short cut for some operations
    ui->actionSTL_file->setShortcut(tr("Shift+S"));
    ui->actionMOD_file_2->setShortcut(tr("Shift+M"));
    ui->changeColorItor->setShortcut(tr("Ctrl+I"));
    ui->color->setShortcut(tr("Alt+C"));
    ui->objectColor->setShortcut(tr("Shift+C"));
    ui->camera->setShortcut(tr("Ctrl+R"));

    // set the position of the text on the label
    ui->lightLabel->setAlignment(Qt::AlignCenter);
    ui->objectColorLabel->setAlignment(Qt::AlignCenter);

    // set the range of the spin box and its initial value, single step
    ui->intensity->setMinimum(0);
    ui->intensity->setMaximum(1);
    ui->intensity->setValue(0.3);
    ui->intensity->setSingleStep(0.1);

    // set the range of the slider and its initial value
    ui->intensitySlider->setMinimum(0);
    ui->intensitySlider->setMaximum(10);
    ui->intensitySlider->setValue(3);

    // disable all meanless widget before loading a model
    ui->intensity->setEnabled(false);
    ui->intensitySlider->setEnabled(false);
    ui->removeLight->setEnabled(false);
    ui->changeColorItor->setEnabled(false);
    ui->color->setEnabled(false);
    ui->objectColor->setEnabled(false);
    ui->edgeCheck->setEnabled(false);
    ui->noFilter->setEnabled(false);
    ui->clipfilter->setEnabled(false);
    ui->shrinkfilter->setEnabled(false);
    ui->camera->setEnabled(false);

    // set initial state of check box and radio buttons
    ui->edgeCheck->setChecked(false);
    ui->noFilter->setChecked(true);
    ui->noShape->setChecked(true);

    // create a button group for radio buttons (filter)
    QButtonGroup* filterButton = new QButtonGroup(this);
    filterButton->addButton(ui->noFilter, 0);
    filterButton->addButton(ui->clipfilter, 1);
    filterButton->addButton(ui->shrinkfilter, 2);

    // create a button group for radio vuttons (primitive shape)
    QButtonGroup* shapeButton = new QButtonGroup(this);
    shapeButton->addButton(ui->noShape, 0);
    shapeButton->addButton(ui->pyramid, 1);
    shapeButton->addButton(ui->tetrahedron, 2);
    shapeButton->addButton(ui->hexahedron, 3);

    // initialize the vector for light color
	for (size_t i = 0; i < 3; i++)
	{
		value.push_back(1);
	}

    // connect operations to its widgets
    connect(ui->actionSTL_file, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->color, SIGNAL(clicked()), this, SLOT(setLightColor()));
    connect(ui->intensity, SIGNAL(valueChanged(double)), this, SLOT(setLightIntensitySpinBox()));
    connect(ui->intensitySlider, SIGNAL(valueChanged(int)), this, SLOT(setLightIntensitySlider()));
    connect(ui->removeLight, SIGNAL(clicked()), this, SLOT(resetLight()));
    connect(ui->changeColorItor, SIGNAL(clicked()), this, SLOT(changModelColorItor()));
    connect(ui->objectColor, SIGNAL(clicked()), this, SLOT(selectedObjectColor()));
    connect(ui->edgeCheck, SIGNAL(stateChanged(int)), this, SLOT(visableEdge(int)));
    connect(ui->backgroundColor, SIGNAL(clicked()), this, SLOT(setBackgroundColor()));
    connect(filterButton, SIGNAL(buttonClicked(int)), this, SLOT(applyFilter(int)));
    connect(shapeButton, SIGNAL(buttonClicked(int)), this, SLOT(primitiveShape(int)));
    //connect(shapeButton, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &MainWindow::primitiveShape);
    connect(ui->camera, SIGNAL(clicked()), this, SLOT(resetCamera()));
    connect(ui->actionMOD_file_2, SIGNAL(triggered()), this, SLOT(openMODFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// this function would load the STL file
void MainWindow::open()
{
    // remove all the actors
    for(shapeItor = primitiveShapeActor.begin(); shapeItor != primitiveShapeActor.end(); shapeItor++)
    {
        renderer->RemoveActor(*shapeItor);
    }
    renderer->RemoveActor(shapeActor);
    ui->noShape->setChecked(true);

    // set the filter for STL file
    QString filter = "STL file (*.stl)";
    // obtain the file name
    QString filename = QFileDialog::getOpenFileName(this, QString("Open STL file"), "D:\\year 3\\Project\\Computing\\STL+Model+Files-20200202", filter);

    // if file name is invalid then terminate the function
    if(filename.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Invalid file name", QMessageBox::Ok);
        return;
    }

    // read the file
    STLReader->SetFileName(filename.toLatin1().data());
    STLReader->Update();

    mapper->SetInputConnection(STLReader->GetOutputPort());

    // set properties and date of the actor
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color->GetColor3d("Blue").GetData());

    // render the actor
    renderer->AddActor(actor);

    ui->openGLWidget->GetRenderWindow()->AddRenderer(renderer);
    ui->openGLWidget->GetRenderWindow()->Render();

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    // enable some of the meaningful operations after loading the file
    ui->color->setEnabled(true);
    ui->intensity->setEnabled(true);
    ui->intensitySlider->setEnabled(true);
    ui->changeColorItor->setEnabled(true);
    ui->objectColor->setEnabled(true);
    ui->edgeCheck->setEnabled(true);
    ui->noFilter->setEnabled(true);
    ui->clipfilter->setEnabled(true);
    ui->shrinkfilter->setEnabled(true);
    ui->camera->setEnabled(true);
}

// this function would set color of the light
void MainWindow::setLightColor()
{
    // create a map, the key is bool and value is vector<double>
    map<bool, vector<double>> result;
    // obtain the return value from the dialog
    result = DialogColor::getValue();

    // if the input of the dialog is accepted then change the parameters of the light
    if(result.find(QDialog::Accepted) != result.end())
    {
        // obtain RGB value of new color
        value = result[QDialog::Accepted];
        // set light color
        light->SetColor(value[0], value[1], value[2]);
        // add the light to the renderer
        renderer->AddLight(light);
        ui->openGLWidget->GetRenderWindow()->Render();

        // enable reset light operation
        ui->removeLight->setEnabled(true);
    }
}

// this function would set intensity of the light
void MainWindow::setLightIntensitySpinBox()
{
    // obtain the value fron the spin box
    intensity = ui->intensity->text().toDouble();
    ui->intensitySlider->setValue(intensity * 10);

    // set light intensity
    light->SetIntensity(intensity);
    // add new light source to renderer
    renderer->AddLight(light);
    ui->openGLWidget->GetRenderWindow()->Render();

    // enable reset light operation
    ui->removeLight->setEnabled(true);
}

void MainWindow::setLightIntensitySlider()
{
    // obtain the value fron the slider
    intensity = ui->intensitySlider->value() / 10.0;
    ui->intensity->setValue(intensity);

    // set light intensity
    light->SetIntensity(intensity);
    // add new light source to renderer
    renderer->AddLight(light);
    ui->openGLWidget->GetRenderWindow()->Render();

    // enable reset light operation
    ui->removeLight->setEnabled(true);
}

// this function would reset light
void MainWindow::resetLight()
{
    // remove all the lights
    renderer->RemoveAllLights();
    ui->openGLWidget->GetRenderWindow()->Render();

    // disable reset light operation
    ui->removeLight->setEnabled(false);
}

// this function could change the object color in sequence red->blue->red
// if color is neither red nor blue, the color would set to blue
void MainWindow::changModelColorItor()
{
    // allocate momory for store current object color
    double temp[3];
    // obtain the current object color
    for(size_t i = 0; i < 3; i++)
    {
        temp[i] = actor->GetProperty()->GetColor()[i];
    }

    // if current color is red
    if(temp[0] == 1 && temp[1] == 0 && temp[2] == 0)
    {
        // change color to blue
        actor->GetProperty()->SetColor(color->GetColor3d("Blue").GetData());
    }
    // if current color is not red
    else
    {
        // change color to blue
        actor->GetProperty()->SetColor(color->GetColor3d("Red").GetData());
    }

    // render the object
    renderer->AddActor(actor);
    ui->openGLWidget->GetRenderWindow()->Render();
}

// this function could chang the object color to a user selected one
void MainWindow::selectedObjectColor()
{
    double redComponent, greenComponent, blueConponent;
    // obtain the color selected by user
    QColor selectedColor = QColorDialog::getColor(Qt::white, this,
                                           "Select the object color", QColorDialog::ShowAlphaChannel);
    // check the validity of the selected color
    if(!selectedColor.isValid())
    {
        return ;
    }

    // calculate the RGB conponents
    redComponent = selectedColor.red() / 255.0;
    greenComponent = selectedColor.green() / 255.0;
    blueConponent = selectedColor.blue() / 255.0;

    // render the actor using the new color
    actor->GetProperty()->SetColor(redComponent, greenComponent, blueConponent);
    ui->openGLWidget->GetRenderWindow()->Render();
}

// this function could set the edge visibility of the object
void MainWindow::visableEdge(int checked)
{
    // if the check box is checked, show edge
    if(checked)
    {
        actor->GetProperty()->EdgeVisibilityOn();
    }
    else
    {
        actor->GetProperty()->EdgeVisibilityOff();
    }

    ui->openGLWidget->GetRenderWindow()->Render();
}

// this function could set background color
void MainWindow::setBackgroundColor()
{
    double redComponent, greenComponent, blueConponent;
    // obtain the color selected by user
    QColor selectedColor = QColorDialog::getColor(Qt::white, this,
                                           "Select the object color", QColorDialog::ShowAlphaChannel);
    // check the validity of the selected color
    if(!selectedColor.isValid())
    {
        return ;
    }

    // calculate the RGB conponents
    redComponent = selectedColor.red() / 255.0;
    greenComponent = selectedColor.green() / 255.0;
    blueConponent = selectedColor.blue() / 255.0;

    // render the new background
    renderer->SetBackground(redComponent, greenComponent, blueConponent);
    ui->openGLWidget->GetRenderWindow()->Render();
}

// this function could apply filter settings
void MainWindow::applyFilter(int buttonID)
{
    switch(buttonID)
    {
    case 0:
    {
        mapper->SetInputConnection(STLReader->GetOutputPort());
        actor->SetMapper(mapper);
        break;
    }

    case 1:
    {
        vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
        plane->SetOrigin(0, 0, 0);
        plane->SetNormal(-1, 0, 0);
        vtkSmartPointer<vtkClipDataSet> filter = vtkSmartPointer<vtkClipDataSet>::New();
        filter->SetInputConnection(STLReader->GetOutputPort());
        filter->SetClipFunction(plane.Get());
        mapper->SetInputConnection(filter->GetOutputPort());
        actor->SetMapper(mapper);
        break;
    }

    case 2:
    {
        vtkSmartPointer<vtkShrinkFilter> filter = vtkSmartPointer<vtkShrinkFilter>::New();
        filter->SetInputConnection(STLReader->GetOutputPort());
        filter->SetShrinkFactor(0.8);
        filter->Update();
        mapper->SetInputConnection(filter->GetOutputPort());
        actor->SetMapper(mapper);
        break;
    }
    }

    ui->openGLWidget->GetRenderWindow()->Render();
}

// this function could add one of the primitive shapes
void MainWindow::primitiveShape(int checked)
{
    // remove all the actors
    renderer->RemoveActor(actor);
    for(shapeItor = primitiveShapeActor.begin(); shapeItor != primitiveShapeActor.end(); shapeItor++)
    {
        renderer->RemoveActor(*shapeItor);
    }
    // remove light
    renderer->RemoveLight(light);

    // render primitive shape selected by user
    switch(checked)
    {
    case 0:
    {
        renderer->RemoveActor(shapeActor);

        break;
    }
    // render pyramid
    case 1:
    {
        vtkSmartPointer<vtkPyramid> pyramid = vtkSmartPointer<vtkPyramid>::New();
        vtkSmartPointer<vtkPoints> point = vtkSmartPointer<vtkPoints>::New();
        float p0[3] = {1, 1, 1};
        float p1[3] = {-1, 1, 1};
        float p2[3] = {-1, -1, 1};
        float p3[3] = {1, -1, 1};
        float p4[3] = {0, 0, 0};
        float* data[5] = {p0, p1, p2, p3, p4};

        for(size_t i = 0; i < 5; i++)
        {
            point->InsertNextPoint(data[i]);
            pyramid->GetPointIds()->SetId(i, i);
        }

        vtkSmartPointer<vtkCellArray> cell = vtkSmartPointer<vtkCellArray>::New();
        cell->InsertNextCell(pyramid);

        vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New();
        ug->SetPoints(point);
        ug->InsertNextCell(pyramid->GetCellType(), pyramid->GetPointIds());

        vtkSmartPointer<vtkDataSetMapper> pyramidMapper = vtkSmartPointer<vtkDataSetMapper>::New();
        pyramidMapper->SetInputData(ug);

        shapeActor->SetMapper(pyramidMapper);
        renderer->AddActor(shapeActor);
        break;
    }
    // render tetrahedron
    case 2:
    {
        vtkSmartPointer<vtkTetra> tetra = vtkSmartPointer<vtkTetra>::New();
        vtkSmartPointer<vtkPoints> point = vtkSmartPointer<vtkPoints>::New();

        point->InsertNextPoint(0, 0, 0);
        point->InsertNextPoint(1, 0, 0);
        point->InsertNextPoint(0, 1, 0);
        point->InsertNextPoint(0, 0, 1);

        for(size_t i = 0; i < 4; i++)
        {
            tetra->GetPointIds()->SetId(i, i);
        }

        vtkSmartPointer<vtkCellArray> cell = vtkSmartPointer<vtkCellArray>::New();
        cell->InsertNextCell(tetra);

        vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New();
        ug->SetPoints(point);
        ug->SetCells(VTK_TETRA, cell);

        vtkSmartPointer<vtkDataSetMapper> tetraMapper = vtkSmartPointer<vtkDataSetMapper>::New();
        tetraMapper->SetInputData(ug);

        shapeActor->SetMapper(tetraMapper);
        renderer->AddActor(shapeActor);

        break;
    }
    // render hexahedron
    case 3:
    {
        vtkSmartPointer<vtkHexahedron> hex = vtkSmartPointer<vtkHexahedron>::New();
        vtkSmartPointer<vtkPoints> point = vtkSmartPointer<vtkPoints>::New();
        float p0[3] = {0, 0, 0};
        float p1[3] = {1, 0, 0};
        float p2[3] = {1, 1, 0};
        float p3[3] = {0, 1, 0};
        float p4[3] = {0, 0, 1};
        float p5[3] = {1, 0, 1};
        float p6[3] = {1, 1, 1};
        float p7[3] = {0, 1, 1};
        float* data[8] = {p0, p1, p2, p3, p4, p5, p6, p7};

        for(size_t i = 0; i < 8; i++)
        {
            point->InsertNextPoint(data[i]);
            hex->GetPointIds()->SetId(i, i);
        }

        vtkSmartPointer<vtkCellArray> cell = vtkSmartPointer<vtkCellArray>::New();
        cell->InsertNextCell(hex);

        vtkSmartPointer<vtkUnstructuredGrid> ug = vtkSmartPointer<vtkUnstructuredGrid>::New();
        ug->SetPoints(point);
        ug->InsertNextCell(hex->GetCellType(), hex->GetPointIds());

        vtkSmartPointer<vtkDataSetMapper> hexMapper = vtkSmartPointer<vtkDataSetMapper>::New();
        hexMapper->SetInputData(ug);

        shapeActor->SetMapper(hexMapper);
        renderer->AddActor(shapeActor);

        break;
    }
    }

    ui->openGLWidget->GetRenderWindow()->Render();

    // disable some functions
    ui->intensity->setEnabled(false);
    ui->intensitySlider->setEnabled(false);
    ui->removeLight->setEnabled(false);
    ui->changeColorItor->setEnabled(false);
    ui->color->setEnabled(false);
    ui->objectColor->setEnabled(false);
    ui->edgeCheck->setEnabled(false);
    ui->noFilter->setEnabled(false);
    ui->clipfilter->setEnabled(false);
    ui->shrinkfilter->setEnabled(false);
    ui->camera->setEnabled(true);

    // reset all other functions
    ui->noFilter->setChecked(true);
    ui->edgeCheck->setChecked(false);
}

// this function could reset camera
void MainWindow::resetCamera()
{
    // set camera parameters
    camera->SetPosition(10, 0, 0);
    camera->SetFocalPoint(0, 0, 0);
    camera->SetClippingRange(-10, 10);
    camera->SetViewUp(0, 0, 0);

    // set active camera for randerer
    renderer->SetActiveCamera(camera);
    ui->openGLWidget->GetRenderWindow()->Render();

}

// this function could open a mod file
void MainWindow::openMODFile()
{
    // set the file format and get file name
    QString filter = "MOD file (*.mod)";
    QString filename = QFileDialog::getOpenFileName(this, QString("Open MOD file"), "D:\\year 3\\Project\\Computing\\Model files", filter);

    // if the file name is invalid then terminate the function
    if(filename.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Invalid file name", QMessageBox::Ok);
        return;
    }

    // read the file and declare vectors to store the data
    Model loadMOD(filename.toStdString());
    vector<Tetrahedron> tetrData = loadMOD.getTetra();
    vector<Pyramid> pyramidData = loadMOD.getPyramid();
    vector<Hexahedron> hexData = loadMOD.getHex();

    // obtain the number of the primitive shapes
    int shapeNumber = hexData.size() + pyramidData.size() + tetrData.size();

    // declare vectors to store the actor for primitive shapes
    vector<vtkSmartPointer<vtkHexahedron>> hexSource(hexData.size());
    vector<vtkSmartPointer<vtkPyramid>> pyramidSource(pyramidData.size());
    vector<vtkSmartPointer<vtkTetra>> tetrSource(tetrData.size());

    // remove all the actors
    for(shapeItor = primitiveShapeActor.begin(); shapeItor != primitiveShapeActor.end(); shapeItor++)
    {
        renderer->RemoveActor(*shapeItor);
    }
    renderer->RemoveActor(actor);
    renderer->RemoveActor(shapeActor);
    // remove light
    renderer->RemoveLight(light);

    // declare a vector to store all the information related to actors
    primitiveShapeActor.resize(shapeNumber);
    vector<vtkSmartPointer<vtkCellArray>> cellData(shapeNumber);
    vector<vtkSmartPointer<vtkPoints>> pointData(shapeNumber);
    vector<vtkSmartPointer<vtkUnstructuredGrid>> ugData(shapeNumber);
    vector<vtkSmartPointer<vtkDataSetMapper>> mapperData(shapeNumber);


    // declare variable for iteration
    size_t i, j, k;

    for(i = 0; i < hexData.size(); i++)
    {
        hexSource[i] = vtkSmartPointer<vtkHexahedron>::New();
        pointData[i] = vtkSmartPointer<vtkPoints>::New();
		primitiveShapeActor[i] = vtkSmartPointer<vtkActor>::New();

        float p0[3] = {hexData[i].getVertex()[0].get_i(), hexData[i].getVertex()[0].get_j(), hexData[i].getVertex()[0].get_k()};
        float p1[3] = {hexData[i].getVertex()[1].get_i(), hexData[i].getVertex()[1].get_j(), hexData[i].getVertex()[1].get_k()};
        float p2[3] = {hexData[i].getVertex()[2].get_i(), hexData[i].getVertex()[2].get_j(), hexData[i].getVertex()[2].get_k()};
        float p3[3] = {hexData[i].getVertex()[3].get_i(), hexData[i].getVertex()[3].get_j(), hexData[i].getVertex()[3].get_k()};
        float p4[3] = {hexData[i].getVertex()[4].get_i(), hexData[i].getVertex()[4].get_j(), hexData[i].getVertex()[4].get_k()};
        float p5[3] = {hexData[i].getVertex()[5].get_i(), hexData[i].getVertex()[5].get_j(), hexData[i].getVertex()[5].get_k()};
        float p6[3] = {hexData[i].getVertex()[6].get_i(), hexData[i].getVertex()[6].get_j(), hexData[i].getVertex()[6].get_k()};
        float p7[3] = {hexData[i].getVertex()[7].get_i(), hexData[i].getVertex()[7].get_j(), hexData[i].getVertex()[7].get_k()};

        float* data[8] = {p0, p1, p2, p3, p4, p5, p6, p7};

        for(size_t m = 0; m < 8; m++)
        {
            pointData[i]->InsertNextPoint(data[m]);
            hexSource[i]->GetPointIds()->SetId(m, m);
        }

        cellData[i] = vtkSmartPointer<vtkCellArray>::New();
        cellData[i]->InsertNextCell(hexSource[i]);

        ugData[i] = vtkSmartPointer<vtkUnstructuredGrid>::New();
        ugData[i]->SetPoints(pointData[i]);
        ugData[i]->InsertNextCell(hexSource[i]->GetCellType(), hexSource[i]->GetPointIds());

        mapperData[i] = vtkSmartPointer<vtkDataSetMapper>::New();
        mapperData[i]->SetInputData(ugData[i]);

        primitiveShapeActor[i]->SetMapper(mapperData[i]);
    }


    for(size_t n = 0; n < primitiveShapeActor.size(); n++)
    {
        renderer->AddActor(primitiveShapeActor[n]);
    }
    ui->openGLWidget->GetRenderWindow()->Render();

    // reset all other functions
    ui->noShape->setChecked(true);
    ui->noFilter->setChecked(true);
    ui->edgeCheck->setChecked(false);

    // disable some functions
    ui->intensity->setEnabled(false);
    ui->intensitySlider->setEnabled(false);
    ui->removeLight->setEnabled(false);
    ui->changeColorItor->setEnabled(false);
    ui->color->setEnabled(false);
    ui->objectColor->setEnabled(false);
    ui->edgeCheck->setEnabled(false);
    ui->noFilter->setEnabled(false);
    ui->clipfilter->setEnabled(false);
    ui->shrinkfilter->setEnabled(false);
    ui->camera->setEnabled(true);
}
