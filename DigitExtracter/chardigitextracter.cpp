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
#include "chardigitextracter.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QDir>

using namespace std;
using namespace cv;

CharDigitExtracter::CharDigitExtracter(QString dataPath)
{
    reader = new DigitReader(dataPath, 400, 50);
}

DigitResult* CharDigitExtracter::extract(Mat &src, bool do_normalize) {
    DigitResult* dresult = new DigitResult(1,1);
    vector<DigitInfo> results(25);
    dresult->result = results;

    float startY, startX, square_size;
    pre_extract(src, do_normalize, startX, startY, square_size);

    Rect box_decimal, box_fraction;
    Mat digit;
    float total = 0;
    for(int i = 0; i < 25; i++) {
        //accuracy
        int a1 = 0;
        int a2 = 0;
        //decimal extract
        box_decimal = Rect(startX - square_size*4/6, startY + square_size/10, square_size*2/3, square_size*5/6);
        rectangle(src, box_decimal, Scalar(150));
        digit = src(box_decimal);
        digit = DigitReader::preprocessing(digit, 50, 50);
        total = reader->classify(digit, a1);

        //fraction extract
        box_fraction = Rect(startX + square_size/6, startY + square_size/10, square_size*2/3, square_size*5/6);
        rectangle(src, box_fraction, Scalar(150));
        digit = src(box_fraction);
        digit = DigitReader::preprocessing(digit, 50, 50);
        total = total + reader->classify(digit, a2)/10;

        dresult->result[i].score = total;
        dresult->result[i].accuracy = (a1+a2)/2;
        startY = floor(startY + square_size);
    }

    emit extractFinished(dresult);
    return dresult;
}
