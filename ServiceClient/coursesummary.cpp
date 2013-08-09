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

#include "coursesummary.h"

CourseSummary::CourseSummary()
{
}

CourseSummaryList::CourseSummaryList() {

}

int CourseSummaryList::rowCount(const QModelIndex &parent) const{
    return size();
}

int CourseSummaryList::columnCount(const QModelIndex &parent) const{
    return 9;
}

QVariant CourseSummaryList::data(const QModelIndex &index, int role) const{
    if(index.column() >= columnCount() || index.row() >= size()) {
        return QVariant();
    }

    if(role == Qt::DisplayRole) {
        CourseSummary s = at(index.row());
        switch(index.column()) {
        case 0: return index.column()+1;
        case 1: return s.course_id;
        case 2: return s.term;
        case 3: return s.year;
        case 4: return s.subject;
        case 5: return s.credits;
        case 6: return s.percent;
        case 7: return s.description;
        case 8: return s.lecturer;
        }
    }
    return QVariant();
}
