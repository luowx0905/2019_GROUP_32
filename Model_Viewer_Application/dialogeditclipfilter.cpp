#include "dialogeditclipfilter.h"
#include "ui_dialogeditclipfilter.h"

DialogEditClipFilter::DialogEditClipFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditClipFilter)
{
    ui->setupUi(this);
}

DialogEditClipFilter::~DialogEditClipFilter()
{
    delete ui;
}
