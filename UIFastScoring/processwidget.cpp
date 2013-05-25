#include "processwidget.h"
#include "ui_processwidget.h"
#include <QFileDialog>

ProcessWidget::ProcessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessWidget)
{
    ui->setupUi(this);
    pointExtracter = new PointDigitExtracter();
}

ProcessWidget::~ProcessWidget()
{
    delete ui;
}

void ProcessWidget::SelectScanFolder() {
    ui->txtPath->setText(QFileDialog::getExistingDirectory(this, "Open Directory"));
}
