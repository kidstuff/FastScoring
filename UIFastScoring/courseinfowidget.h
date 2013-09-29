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

#ifndef COURSEINFOWIDGET_H
#define COURSEINFOWIDGET_H

#include "serviceclient.h"
#include "formprinter.h"
#include "coursesummary.h"
#include "response.h"
#include <QTabWidget>
#include <QUrlQuery>
#include <QtPrintSupport/QPrintPreviewWidget>
#include <QtPrintSupport/QPrintPreviewDialog>

namespace Ui {
class CourseInfoWidget;
}

class CourseInfoWidget : public QTabWidget
{
    Q_OBJECT
    
public:
    explicit CourseInfoWidget(QWidget *parent = 0);
    ~CourseInfoWidget();
    FormPrinter* fprinter;
    //QPrintPreviewWidget* preview;
    QPrintPreviewDialog* preview;
    QPrinter* printer;
public slots:
    void LoadCourseList();
    void DisplayCourseList(CourseSummaryList* sumary, Response r);
    void Print();
    void printpre(QPrinter* printer);

signals:
    //void PrintClicked(CourseInfo*);
    void PrintClicked(QPrinter*);
    void GetCourseList(QString year, QString term, QString faculty,
                       QString supject, QString lecturer, QUrlQuery* extra);
private:
    Ui::CourseInfoWidget *ui;

};

#endif // COURSEINFOWIDGET_H
