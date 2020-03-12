#ifndef DIALOGEDITSHRINKFILTER_H
#define DIALOGEDITSHRINKFILTER_H

#include <QDialog>

namespace Ui {
class dialogEditShrinkFilter;
}

class dialogEditShrinkFilter : public QDialog
{
    Q_OBJECT

public:
    explicit dialogEditShrinkFilter(QWidget *parent = nullptr, double startingValue = 1);
    ~dialogEditShrinkFilter();
public slots:
    void handleShrinkFactorSlider(int);
    void handleShrinkFactorSpinBox(double);
signals:
    void shrinkFactorChanged(double);

private:
    Ui::dialogEditShrinkFilter *ui;
    double shrinkFactor;
};

#endif // DIALOGEDITSHRINKFILTER_H
