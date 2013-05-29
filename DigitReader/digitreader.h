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
#ifndef READER_H
#define READER_H
#include <opencv2/opencv.hpp>
#include <QString>

using namespace cv;
using namespace std;

class DigitReader {
public:
    DigitReader(QString path, int num_sample, int sample_size);
    float classify(Mat& imgSrc,int& accuracy);
    int test();
    static Mat preprocessing(Mat& imgSrc, int new_width, int new_height);
private:
    static const int K = 10;
    QString file_path;
    int train_samples;
    int size;
    Mat trainData;
    Mat trainClasses;
    KNearest knn;
    bool getData();
    void train();
};

#endif // READER_H
