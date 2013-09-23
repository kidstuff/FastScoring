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
#ifndef FORMPRINTER_H
#define FORMPRINTER_H

#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <vector>
#include "courseinfo.h"

using namespace std;

class FormPrinter
{
public:
    FormPrinter(vector<int> steps);
    enum FormType {CHAR, POINT};

public slots:
    void Print(CourseInfo* r);
    CourseInfo* generatedata(int n);
private:
    vector<int> odd_steps;
    QPrinter *printer;
    QPainter *painter;
    int n;
    double h1;
    double h2;
    int text_height;
    void print_header(CourseInfo* r,QPoint p);
    void print_footer(CourseInfo* r,QPoint p);

    void print_table(CourseInfo* r);
        void print_cl_number(CourseInfo* r,QPoint p); //0,2222,400
        void print_cl_stid(CourseInfo* r,QPoint p);//400,1200
        void print_cl_stname(CourseInfo* r,QPoint);//1600,2200
        void print_cl_stbirth(CourseInfo* r,QPoint p);//3800,650
        void print_cl_stmark(CourseInfo* r,QPoint p);//5450,1200
        void print_cl_stringmark(QPoint p);//6650,400
        void print_cl_stpagenum(QPoint p);//7050,1100
        void print_cl_stsignature(QPoint p);//8150
        void print_cl_stcode(CourseInfo* r,QPoint p);

    void print_line1(QPoint p);
    void print_line2(QPoint p);
    void print_line3(QPoint p);
    void print_line4(QPoint p);
    void print_line5(QPoint p);
    void print_line6(QPoint p);
    void print_line7(QPoint p);
    void print_number(int num, QPoint p);
    void print_pagecode(QPoint p);
    void print_rectangle(QPoint p);
};

#endif // FORMPRINTER_H
