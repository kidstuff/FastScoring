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

#ifndef COURSEINFO_H
#define COURSEINFO_H

#include "student.h"
#include <QAbstractTableModel>
#include <QDomElement>

class CourseInfo : public QAbstractTableModel
{
    Q_OBJECT
public:
    CourseInfo(QDomElement xml);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QDomElement toDomElement();
    QList<Student> students;
    QString course_id;
    QString subject_name;
    QString subject_id;
    QString teacher;
    QString teacher_id;
    QString faculty;
    QString faculty_id;
    //header
    QString school_name;
    QString room_name;
    QString rp_id;
    QString rp_day;
    QString rp_title;
    QString term;
    QString year;
    QString subject;
    QString credits;
    QString percent;
    QString description;
    QString exam_day;
    QString exam_room;
    //table header
    const QString tb_stt;
    const QString tb_mahs;
    const QString tb_hoten;
    const QString tb_ngsinh;
    const QString tb_diem;
    const QString tb_diemchu;
    const QString tb_st;
    const QString tb_chuky;
    const QString tb_lop;
    //left footer
    const QString auth;
    const QString sign;
    //right footer
    QString rpft_day;
    QString teach;
};

#endif // COURSEINFO_H
