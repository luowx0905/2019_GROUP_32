#ifndef DIALOGEDITCLIPFILTER_H
#define DIALOGEDITCLIPFILTER_H

#include <QDialog>

namespace Ui {
class DialogEditClipFilter;
}

class DialogEditClipFilter : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditClipFilter(QWidget *parent = nullptr);
    ~DialogEditClipFilter();

private:
    Ui::DialogEditClipFilter *ui;
};

#endif // DIALOGEDITCLIPFILTER_H
