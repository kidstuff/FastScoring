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
    /**
     * @brief minRat minimum ratio of width/height to be a square
     */
    static const float minRat = 0.9;
    /**
     * @brief maxRat maximum ratio for width/height to be a square
     */
    static const float maxRat = 1.1;
public slots:
    /**
     * @brief extract virtual method that should extract data from src image
     * @param src reference to cv::Mat source
     * @param do_normalize determind if the image need to be normalize
     * (re-format) or not
     * @return a list of point data
     */
    virtual vector<float> extract(Mat &src, bool do_normalize) = 0;
protected:
    /**
     * @brief The ControlShape struct is a square with for point
     */
    struct ControlShape {
        Point top_left;
        Point top_right;
        Point bottom_left;
        Point bottom_right;
    };
    static bool sortArrayPointSize(vector<Point> a, vector<Point> b);
    static bool sortPointY(Point a, Point b);
    static double distance(Point a, Point b);
    /**
     * @brief is_square deteminde if the contour is a square or not, fill the
     * shape it true.
     * @param contour an vector(or you can say list) of point (a line)
     * @param shape the out shape that you can use.
     * @return
     */
    static bool is_square(vector<Point>& contour, ControlShape &shape);
    /**
     * @brief fill_shape find 4 conors of a square and put it to the shape
     * @param corners your corners
     * @param shape your square
     */
    static void fill_shape(vector<Point>& corners, ControlShape& shape);
    /**
     * @brief pre_extract filter noise and threshold src
     * @param src the source image - need to be 1 channel(grayscale) image
     * @param do_normalize determind if the image need to be normalize or not.
     * @param startY the begin X position of data area
     * @param startX the begin Y position of data area
     * @param square_size every line of data should has relative with this
     */
    static void pre_extract(Mat &src, bool do_normalize, float& startY, float& startX, float& square_size);
    /**
     * @brief normalize rotate the src if need
     * @param src orgin cv:Mat image
     * @param dst destinate (rotated) image
     * @param shapea the upper square in the paper
     * @param shapeb the lower squre in the paper
     * @param avgW average width of square
     * @param avgH average height of square
     * @return
     */
    static bool normalize(Mat &src, Mat &dst, ControlShape& shapea, ControlShape& shapeb, float avgW, float avgH);
};

#endif // DIGITEXTRACTER_H
