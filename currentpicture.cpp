#include "currentpicture.h"
#include <opencv2/core.hpp>
#include <stdlib.h>
#include<iostream>
#include <opencv2/imgproc.hpp>

using namespace cv;

CurrentPicture::CurrentPicture(QString fname, QPixmap pmap):filename_{fname}, pixmap_{pmap} {
    mat_ = imread(fname.toStdString(), IMREAD_COLOR);
}

void CurrentPicture::Change(QString filename, QPixmap map){
    filename_ = filename;
    pixmap_ = map;
    mat_ = imread(filename_.toStdString(), IMREAD_COLOR);
}

void CurrentPicture::changeRGB(int val, int channel){
    Mat bgr[3];
    split(mat_, bgr);
    bgr[channel] += val;
    merge(bgr, 3, current_mat);
}

void CurrentPicture::changeR(int val){
    changeRGB(val, 2);
    ctype = CurChangeType::R;
}

void CurrentPicture::changeG(int val){
    changeRGB(val, 1);
    ctype = CurChangeType::G;
}

void CurrentPicture::changeB(int val){
    changeRGB(val, 0);
    ctype = CurChangeType::B;
}

void CurrentPicture::changeHSV(int val, int channel){
    Mat hsv[3];
    Mat temp;
    cvtColor(mat_, temp, COLOR_BGR2HSV);
    split(temp, hsv);
    hsv[channel] += val;
    merge(hsv, 3, temp);
    cvtColor(temp, current_mat, COLOR_HSV2BGR);
}

void CurrentPicture::changeH(int val){
    changeHSV(val, 0);
    ctype = CurChangeType::H;
}

void CurrentPicture::changeS(int val){
    changeHSV(val, 1);
    ctype = CurChangeType::S;
}

void CurrentPicture::changeV(int val){
    changeHSV(val, 2);
    ctype = CurChangeType::V;
}

void CurrentPicture::changeL(int val){
    Mat hls[3];
    Mat temp;
    cvtColor(mat_, temp, COLOR_BGR2HLS);
    split(temp, hls);
    hls[1] += val;
    merge(hls, 3, temp);
    cvtColor(temp, current_mat, COLOR_HLS2BGR);
    ctype = CurChangeType::L;
}

bool CurrentPicture::OkPressed(CurChangeType type){
    if (type == ctype){
        mat_.release();
        mat_ = current_mat.clone();
        return true;
    }
    return false;
}

QPixmap CurrentPicture::curmat2pixmap(){
    Mat swapRGB;
    cvtColor(current_mat, swapRGB, cv::COLOR_BGR2RGB);
    QImage qimg{(unsigned char*) swapRGB.data, swapRGB.cols, swapRGB.rows, QImage::Format_RGB888};
    return QPixmap::fromImage(qimg);
}


