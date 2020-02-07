// this file contains the implementation of class DialogColor

#include "dialogcolor.h"
#include "ui_dialogcolor.h"

#include <vector>
#include <map>
#include <memory>
#include <QDialog>
#include <QDebug>
#include <QDoubleValidator>

using std::vector;
using std::map;
using std::unique_ptr;

DialogColor::DialogColor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogColor)
{
    ui->setupUi(this);

    // set range and number of decimals of this validator
    validator = new QDoubleValidator(this);
    validator->setRange(0, 1);
    validator->setDecimals(1);

    // set validator for all QLineEdit objects
    ui->redEdit->setValidator(validator);
    ui->greenEdit->setValidator(validator);
    ui->blueEdit->setValidator(validator);

    // set place holder for all QLineEdit objects
    ui->redEdit->setPlaceholderText("Default value is 0");
    ui->greenEdit->setPlaceholderText("Default value is 0");
    ui->blueEdit->setPlaceholderText("Default value is 0");
}

DialogColor::~DialogColor()
{
    delete ui;
}

// this function could output all valus in QLineEdit objects
vector<double> DialogColor::getOutput()
{
    vector<double> value(3);

    // obtain the text in QLineEdit and convert them to double
    value[0] = ui->redEdit->text().toDouble();
    value[1] = ui->greenEdit->text().toDouble();
    value[2] = ui->blueEdit->text().toDouble();

    return value;
}

// this function could return the result of the dialog
map<bool, vector<double>> DialogColor::getValue()
{
    // create a map to store the output value
    // the key is bool and value is vector<double>
    map<bool, vector<double>> output;

    // create a dialog using C++ smart pointer to avoid memory leak
    unique_ptr<DialogColor> dialog (new DialogColor());

    // if the memory could be allocated
    if(dialog.get())
    {
        // result would store the return status of the dialog
        // QDialog::Accepted or QDialog::Rejected
        // if is QDialog::Accepted the input value will be returned to MainWindow
        bool result = dialog->exec();
        // store all the input value in the dialog
        vector<double> value = dialog->getOutput();
        // sotre both status of dialog and input values
        output[result] = value;
    }

    // return both status of dialog and input values
    return output;
}
