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
#include "pointdigitextracter.h"
#include <opencv2/opencv.hpp>
#include <iostream>

PointDigitExtracter::PointDigitExtracter(vector<int> steps)
{
    odd_steps = steps;
}

DigitResult* PointDigitExtracter::extract(Mat &src, bool do_normalize) {
    DigitResult* dresult = new DigitResult(1,1);
    vector<DigitInfo> results(25);
    dresult->result = results;

    float startY, startX, square_size;
    pre_extract(src, do_normalize, startX, startY, square_size);

    for(int i = 0; i < 25; i++) {
        float decimal = -1.0;
        float fraction = -1.0;

        int tmpX = startX - square_size*4/6;
        for(int j = 10; j >= 0; j--) {
            Rect r(tmpX, startY+square_size*3/7, square_size/2, square_size*7/12);
            Mat box = src(r);
            tmpX = tmpX - square_size/2;
            float white = countNonZero(box);
            float total = r.width*r.height;
            if(white/total < 0.7) {
                rectangle(src, r, Scalar(150));
                decimal = (float)j;
                break;
            }
        }

        if(decimal != -1 && decimal != 10.0) {
            tmpX = startX+square_size/6;
            for(uint j = 0; j < odd_steps.size(); j++) {
                Rect r(tmpX, startY+square_size*3/7, square_size/2, square_size*7/12);
                Mat box = src(r);
                tmpX = tmpX + square_size/2;
                float white = countNonZero(box);
                float total = r.width*r.height;
                if(white/total < 0.7) {
                    rectangle(src, r, Scalar(150));
                    fraction = (float)odd_steps[j]/10.0;
                    break;
                }
            }
        }

        if(decimal == -1 && fraction == -1) {
            dresult->result[i].score = -1;
        } else {
            if(decimal != -1) {
                dresult->result[i].score = decimal;
            }
            if(fraction != -1) {
                dresult->result[i].score = decimal + fraction;
            }

        }
        dresult->result[i].accuracy = 10;
        startY = floor(startY + square_size);
    }

    emit extractFinished(dresult);
    return dresult;
}
