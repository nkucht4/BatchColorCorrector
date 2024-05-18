#include "currentpicture.h"
#include <opencv2/core.hpp>
#include <stdlib.h>
#include<iostream>

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
    Mat arr[3];
    split(mat_, arr);
    std::cout<<"C"<<std::endl;
    if (val > 0){
        add(arr[val], val, arr[val]);
    }
    std::cout<<"D"<<std::endl;
    merge(arr, 3, current_mat);
    std::cout<<"E"<<std::endl;
    imshow("A", current_mat);
    waitKey(0);
}

void CurrentPicture::changeR(int val){
    std::cout<<"A"<<std::endl;
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


