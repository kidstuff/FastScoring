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
#include "digitreader.h"
#include <QString>
#include <iostream>
using namespace std;
using namespace cv;

DigitReader::DigitReader(QString path, int num_sample, int sample_size) {
    //initial
    file_path = path;
    train_samples = num_sample;
    size = sample_size;
    trainData = Mat(train_samples * 10, size * size, CV_32FC1);
    trainClasses = Mat(train_samples * 10, 1, CV_32FC1);
    getData();
    train();
}


bool DigitReader::getData() {
    QString file_name("%1/%2/%3.pbm");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < train_samples; j++) {

            Mat src_img = imread(file_name.arg(file_path).arg(i).arg(j).toStdString(),
                                 CV_LOAD_IMAGE_GRAYSCALE);

            if (src_img.empty()) {
                cout << file_name.arg(file_path).arg(i).arg(j).toStdString();
                return false;
            }
            trainClasses.row(i * train_samples + j) = i;
            DigitReader::preprocessing(src_img, size, size).reshape(0, 1).
                    convertTo(trainData.row(i * train_samples + j), CV_32FC1);
        }
    }

    return true;
}

void DigitReader::train() {
    knn.train(trainData, trainClasses, Mat(), false, K);
}

float DigitReader::classify(Mat &imgSrc, int& accuracy) {
    Mat nearests(1, K, CV_32FC1);
    Mat samples;
    DigitReader::preprocessing(imgSrc, size, size).reshape(0, 1).convertTo(samples, CV_32FC1);
    //cout << samples << "\n";
    float result = knn.find_nearest(samples, K, 0, 0, &nearests, 0);
    accuracy = 0;
    for (int i = 0; i < K; i++) {
        if (nearests.at<float>(i) == result) {
            accuracy++;
        }
    }
    return result;
}

int DigitReader::test() {
    int err = 0;
    int total = 0;
    int accuracy = 0;
    QString file_name("%1/%2/%3.pbm");

    for (int i = 0; i < 10; i++) {
        for (int j = 50; j < 100; j++) {
            Mat src_img = imread(file_name.arg(file_path).arg(i).arg(j).toStdString(),
                                 CV_LOAD_IMAGE_GRAYSCALE);

            if (!src_img.empty()) {
                Mat prs_img = DigitReader::preprocessing(src_img, size, size);
                total++;
                if ((int)classify(prs_img, accuracy) != i) {
                    err++;
                }
            }
        }
    }
    return (err/total)*100;
}

Mat DigitReader::preprocessing(Mat &imgSrc, int new_width, int new_height) {
    Mat result(new_width, new_height, CV_8UC1, 255);
    int minX = 0;
    int minY = 0;
    int maxX = 0;
    int maxY = 0;

    //find maxY
    for (int i = 0; i < imgSrc.rows; i++) {
        for (int j = 0; j < imgSrc.cols; j++) {
            if (imgSrc.at<uchar>(i, j) == 0) {
                maxY = i;
                break;
            }
        }
    }

    //find minY
    for (int i = imgSrc.rows - 1; i >= 0; i--) {
        for (int j = 0; j < imgSrc.cols; j++) {
            if (imgSrc.at<uchar>(i, j) == 0) {
                minY = i;
                break;
            }
        }
    }

    //find maxX
    for (int j = 0; j < imgSrc.cols; j++) {
        for (int i = 0; i < imgSrc.rows; i++) {
            if (imgSrc.at<uchar>(i, j) == 0) {
                maxX = j;
                break;
            }
        }
    }

    //find minX
    for (int j = imgSrc.cols - 1; j >= 0; j--) {
        for (int i = 0; i < imgSrc.rows; i++) {
            if (imgSrc.at<uchar>(i, j) == 0) {
                minX = j;
                break;
            }
        }
    }

    Rect roi;
    roi.x = minX;
    roi.y = minY;
    roi.width = maxX - minX;
    roi.height = maxY - minY;
    Mat bb(imgSrc, roi);

    int size = (roi.width > roi.height) ? roi.width : roi.height;
    Mat tmp(size, size, CV_8UC1, 255);
    bb.copyTo(tmp(Rect((size - roi.width) / 2, (size - roi.height) / 2, roi.width, roi.height)));
    resize(tmp, result, result.size(), 0, 0, INTER_NEAREST);

    return result;
}
