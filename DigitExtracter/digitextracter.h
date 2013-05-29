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
#ifndef DIGITEXTRACTER_H
#define DIGITEXTRACTER_H

#include "opencv2/imgproc/imgproc.hpp"
#include <QObject>

using namespace cv;
using namespace std;

class DigitExtracter : public QObject
{
    Q_OBJECT
public:
    static const float minRat = 0.9;
    static const float maxRat = 1.1;
public slots:
    virtual vector<float> extract(Mat &src, bool do_normalize) = 0;
protected:
    struct ControlShape {
        Point top_left;
        Point top_right;
        Point bottom_left;
        Point bottom_right;
    };
    static bool sortArrayPointSize(vector<Point> a, vector<Point> b);
    static bool sortPointY(Point a, Point b);
    static double distance(Point a, Point b);
    static bool is_square(vector<Point>& contour, ControlShape &shape);
    static bool normalize(Mat &src, Mat &dst, ControlShape& shapea, ControlShape& shapeb, float avgW, float avgH);
    static void fill_shape(vector<Point>& corners, ControlShape& shape);
    static void pre_extract(Mat &src, bool do_normalize, float& startY, float& startX, float& square_size);
};

#endif // DIGITEXTRACTER_H
