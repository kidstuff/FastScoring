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

#include "student.h"
#include "courseinfo.h"

int CourseInfo::rowCount(const QModelIndex &parent) const {
    return students.size();
}

int CourseInfo::columnCount(const QModelIndex &parent) const {
    return 8;
}

QVariant CourseInfo::data(const QModelIndex &index, int role) const {
    if(role != Qt::DisplayRole || index.column() >= 8 || index.row() >= students.size()) {
        return QVariant();
    }
    Student s = students[index.row()];
    switch(index.column()) {
    case 0: return index.column()+1;
    case 1: return s.student_id;
    case 2: return s.last_name;
    case 3: return s.middle_name;
    case 4: return s.first_name;
    case 5: return s.dayofbirth;
    case 6: return s.point;
    }
    return QVariant();
}
