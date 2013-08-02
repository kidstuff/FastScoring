/****************************************************************************
**FastScoring is a program developed entirely based on open source that help
**school staff entering points faster and easier.
**    Copyright (C) 2013  OPEN-VN.ORG Team
**
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU Affero General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**    This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU Affero General Public License for more details.
**
**    You should have received a copy of the GNU Affero General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#include "processwidget.h"
#include "ui_processwidget.h"
#include "globalsetting.h"
#include "pointdigitextracter.h"
#include "chardigitextracter.h"
#include "imagepreview.h"
#include <QFileDialog>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

ProcessWidget::ProcessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessWidget)
{
    ui->setupUi(this);
    if(GlobalSetting::method() == GlobalSetting::CHAR) {
        extracter = new CharDigitExtracter(GlobalSetting::dataPath());
    } else {
        extracter = new PointDigitExtracter(GlobalSetting::steps());
    }
    connect(this, SIGNAL(StartExtract(Mat&,bool)), extracter, SLOT(extract(Mat&,bool)));
}

ProcessWidget::~ProcessWidget()
{
    delete ui;
    delete extracter;
}

void ProcessWidget::SelectScanFolder() {
    ui->txtPath->setText(QFileDialog::getExistingDirectory(this, "Open Directory"));
}

void ProcessWidget::Process() {
    QDir dir(ui->txtPath->text());
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    filters << "*.jpeg" << "*.jpg" << "*.png";
    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList();
    Mat src;
    for(int i = 0; i < list.size(); i++) {
        src = imread(list.at(i).filePath().toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
        if(!src.data) {
            //TODO: notice about error reading image
            continue;
        }
        emit StartExtract(src, GlobalSetting::doNormalize());
        break;
    }
}
