// this file contains the defination of class DialogColor

#ifndef DIALOGCOLOR_H
#define DIALOGCOLOR_H

#include <QDialog>
#include <QDoubleValidator>
#include <vector>
#include <map>

using std::vector;
using std::map;

namespace Ui {
class DialogColor;
}

class DialogColor : public QDialog
{
    Q_OBJECT

public:
    explicit DialogColor(QWidget *parent = nullptr);
    ~DialogColor();

public slots:
    vector<double> getOutput(); // obtain all the value in QLineEdit

public:
    static map<bool, vector<double>> getValue(); // obtain the result returned by this dialog

private:
    Ui::DialogColor *ui;

    QDoubleValidator* validator; // this validator could make the input in the QLineEdit is valid
};

#endif // DIALOGCOLOR_H
