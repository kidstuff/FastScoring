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
#ifndef PROCESSWIDGET_H
#define PROCESSWIDGET_H

#include "pointdigitextracter.h"
#include "chardigitextracter.h"
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
    CharDigitExtracter* charExtracter;

public slots:
    void SelectScanFolder();
    void Process();
signals:
    void StartExtract(Mat& src, bool do_normalize);
};

#endif // PROCESSWIDGET_H
