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

#include "digitresult.h"

DigitResult::DigitResult(long code, char num){
    this->page_code = code;
    this->page_num = num;
}

int DigitResult::rowCount(const QModelIndex &parent) const {
    return this->result.size();
}

int DigitResult::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant DigitResult::data(const QModelIndex &index, int role) const {
    if(role != Qt::DisplayRole || index.column() >= 2 || index.row() >= result.size()) {
        return QVariant();
    }
    DigitInfo inf = result[index.row()];
    switch(index.column()) {
    case 0: return inf.score;
    case 1: return inf.accuracy;
    }
    return QVariant();
}


