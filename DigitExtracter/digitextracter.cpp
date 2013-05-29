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
#include "digitextracter.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>
#include <algorithm>

bool DigitExtracter::sortArrayPointSize(vector<Point> a, vector<Point> b) {
    return (a.size()>b.size());
}

bool DigitExtracter::sortPointY(Point a, Point b) {
    return (a.y < b.y);
}

void DigitExtracter::fill_shape(vector<Point>& corners, ControlShape& shape) {
    sort(corners.begin(), corners.end(), sortPointY);
    if(corners.at(0).x < corners.at(1).x) {
        shape.top_left = corners.at(0);
        shape.top_right = corners.at(1);
    } else {
        shape.top_left = corners.at(1);
        shape.top_right = corners.at(0);
    }
    if(corners.at(2).x < corners.at(3).x) {
        shape.bottom_left = corners.at(2);
        shape.bottom_right = corners.at(3);
    } else {
        shape.bottom_left = corners.at(3);
        shape.bottom_right = corners.at(2);
    }
}

bool DigitExtracter::normalize(Mat &src, Mat &dst, ControlShape &shapea, ControlShape &shapeb, float avgW, float avgH) {
    vector<Point2f> srcPoints(4);
    srcPoints[0] = shapea.bottom_left;
    srcPoints[1] = shapea.bottom_right;
    srcPoints[2] = shapeb.top_right;
    srcPoints[3] = shapeb.top_left;

    vector<Point2f> dstPoints(4);
    dstPoints[0] = shapea.bottom_left;
    dstPoints[1] = Point2f(shapea.bottom_left.x + avgW, shapea.bottom_left.y);
    dstPoints[2] = Point2f(shapea.bottom_left.x + avgW, shapea.bottom_left.y + avgH);
    dstPoints[3] = Point2f(shapea.bottom_left.x, shapea.bottom_left.y + avgH);
    warpPerspective(src, dst, findHomography(srcPoints, dstPoints), src.size());
    return false;
}

double DigitExtracter::distance(Point a, Point b) {
    double i = a.x - b.x;
    double t = a.y - b.y;
    return sqrt(i*i + t*t);
}

bool DigitExtracter::is_square(vector<Point> &contour, ControlShape &shape) {
    vector<Point> approx;
    approxPolyDP(contour, approx, arcLength(contour, true)*0.02, true);
    if(approx.size() == 4) {
        fill_shape(approx, shape);
        return true;
    }
    return false;
}

void DigitExtracter::pre_extract(Mat &src, bool do_normalize,
                                 float &startX, float &startY, float &square_size) {
    //find all contours
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    threshold(src, src, 140, 255, THRESH_BINARY);
    Canny(src, canny_output, 100, 100*2, 5);
    findContours(canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));
    //sort contours base n len
    sort(contours.begin(), contours.end(),sortArrayPointSize);

    //find the mainbox and two equilateral triangle
    Rect box1, box2;
    ControlShape s1, s2;
    int found = 0;
    for(uint i = 1; i< contours.size(); i++) {
        vector<Point> icontor = contours.at(i);
        Rect r = boundingRect(icontor);
        float ratio = (float) r.width/(float) r.height;
        if(minRat <= ratio && ratio <= maxRat) {
            //the right box must not so tall or long
            ControlShape shape;
            if(is_square(icontor, shape)) {
                if(found == 0) {
                    box1 = r;
                    s1 = shape;
                } else if(found == 1) {
                    box2 = r;
                    s2 = shape;
                    break;
                }
                found++;
            }
        }
    }
    float avgW = (distance(s1.top_left, s1.top_right) + distance(s1.bottom_left, s1.bottom_right)
            + distance(s1.top_left, s1.bottom_left) + distance(s1.top_right, s1.bottom_right)
            + distance(s2.top_left, s2.top_right) + distance(s2.bottom_left, s2.bottom_right)
            + distance(s2.top_left, s2.bottom_left) + distance(s2.top_right, s2.bottom_right))/8;

    if(do_normalize) {
        if(s1.top_left.y < s2.top_left.y) {
            float totalH = (distance(s1.bottom_left, s2.top_left) + distance(s1.bottom_right, s2.top_right))/2;
            square_size = (((totalH-avgW*29/60)/(26+(2/3)))+avgW)/2;

            startY = s1.bottom_left.y + square_size*21/60 + square_size;
            startX = s1.bottom_left.x;
            normalize(src, src, s1, s2, square_size, totalH);
        } else {
            float totalH = (distance(s2.bottom_left, s1.top_left) + distance(s2.bottom_right, s1.top_right))/2;
            square_size = (((totalH-avgW*29/60)/(26+(2/3)))+avgW)/2;

            startY = s2.bottom_left.y + square_size*21/60 + square_size;
            startX = s2.bottom_left.x;
            normalize(src, src, s2, s1, square_size, totalH);
        }
    }
}
