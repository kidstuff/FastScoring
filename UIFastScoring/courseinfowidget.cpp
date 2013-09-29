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

#include "formprinter.h"
#include "courseinfowidget.h"
#include "globalsetting.h"
#include "ui_courseinfowidget.h"
#include "mainwindow.h"
#include <QDebug>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrintPreviewWidget>

CourseInfoWidget::CourseInfoWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::CourseInfoWidget)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);


    printer=new QPrinter(QPrinter::HighResolution);
    fprinter=new FormPrinter(printer);
    //preview=new QPrintPreviewWidget(printer,this);
    preview=new QPrintPreviewDialog(printer,this);

    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOutputFileName("sample.pdf");
    printer->setPaperSize(QPrinter::A4);

//    connect(this, &CourseInfoWidget::PrintClicked,
//            fprinter, &FormPrinter::Print);
    connect(this,SIGNAL(PrintClicked(QPrinter*)),this,SLOT(printpre(QPrinter*)));
    connect(ui->btPrint, &QPushButton::clicked,
            this, &CourseInfoWidget::Print);
    connect(preview,SIGNAL(paintRequested(QPrinter*)),this,SLOT(printpre(QPrinter*)));

    preview->showMaximized();
}

void CourseInfoWidget::LoadCourseList() {
    emit GetCourseList("2013", "2", "id-f-123", "id-s-456", "id-l-789", NULL);
}

void CourseInfoWidget::DisplayCourseList(CourseSummaryList *sumary, Response r) {
    ui->tableView->setModel(sumary);
}

CourseInfoWidget::~CourseInfoWidget()
{
    delete ui;
}

void CourseInfoWidget::Print() {
//    CourseInfo* inf;
//    inf=fprinter->generatedata(99);
    emit PrintClicked(printer);
    preview->exec();
}
void CourseInfoWidget::printpre(QPrinter* printer)
{
    fprinter=new FormPrinter(printer);
    CourseInfo* r=fprinter->generatedata(99);
    fprinter->Print(r);

}
