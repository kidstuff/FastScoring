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
#ifndef CHARDIGITEXTRACTER_H
#define CHARDIGITEXTRACTER_H

#include "digitextracter.h"
#include "digitreader.h"

class CharDigitExtracter : public DigitExtracter
{
public:
    /**
     * @brief CharDigitExtracter recieve a dataPath that is the localtion to the
     * OCR learning data.
     * @param dataPath
     */
    CharDigitExtracter(QString dataPath);
public slots:
    /**
     * @brief extract
     * @param src
     * @param do_normalize
     * @return
     */
    vector<float> extract(Mat &src, bool do_normalize);
private:
    DigitReader* reader;
};

#endif // CHARDIGITEXTRACTER_H
