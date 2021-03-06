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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serviceclient.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    showMaximized();
    procWidget = new ProcessWidget();
    courseWidget = new CourseInfoWidget();

    ServiceClient* client = new ServiceClient();

    connect(courseWidget, &CourseInfoWidget::GetCourseList,
            client, &ServiceClient::GetCourseList);
    connect(client, &ServiceClient::GetCourseListFinished,
            courseWidget, &CourseInfoWidget::DisplayCourseList);

    connect(ui->actionCourseList, &QAction::triggered,
            this, &MainWindow::ShowCourseWidget);

    connect(this, &MainWindow::LoginRequest,
            client, &ServiceClient::Login);
    connect(client, &ServiceClient::LoginFinished,
            this, &MainWindow::CheckLoginResponse);
}

MainWindow::~MainWindow() {
    delete ui;
    delete procWidget;
}

void MainWindow::ShowProcWidget() {
    emit LoginRequest(ui->username->text(), ui->password->text());
    //setCentralWidget(procWidget);
}

void MainWindow::ShowCourseWidget() {
    setCentralWidget(courseWidget);
}

void MainWindow::CheckLoginResponse(Response r) {
    if(r.Status == 200) {
        setCentralWidget(procWidget);
    } else {
        QMessageBox::warning(this, "Login fialed",
                             QString::number(r.Status).append(r.Message));
    }
}
