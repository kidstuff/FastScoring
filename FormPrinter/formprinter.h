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

#include <QPrinter>
#include <QPainter>
#include <vector>
#include "datastruct.h"

using namespace std;

class FormPrinter
{
public:
    FormPrinter(vector<int> steps);
    enum FormType {CHAR, POINT};
    void printing(RoomList& r, QString filename, FormType t);
private:
    vector<int> odd_steps;
    QPrinter *printer;
    QPainter *painter;
    void print_header(RoomList& r);
    void print_footer(RoomList& r);
    void print_table_header(RoomList& r);
    void print_table();
    void print_table_data(RoomList& r);
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
