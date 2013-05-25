#ifndef PROCESSWIDGET_H
#define PROCESSWIDGET_H

#include "pointdigitextracter.h"
#include <QWidget>

namespace Ui {
class ProcessWidget;
}

class ProcessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessWidget(QWidget *parent = 0);
    ~ProcessWidget();

private:
    Ui::ProcessWidget *ui;
    PointDigitExtracter* pointExtracter;

public slots:
    void SelectScanFolder();
};

#endif // PROCESSWIDGET_H
