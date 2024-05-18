#ifndef COLORCORRECTOR_H
#define COLORCORRECTOR_H
#include <vector>
#include "imgnode.h"
#include <QString>
#include "currentpicture.h"

class ColorCorrector
{
    std::vector <ImgNode> images_;
    std::vector <std::pair <CurChangeType, int>> order_;
public:
    ColorCorrector();

    void push_back(ImgNode new_element){    images_.push_back(new_element); }
    QString filename_at(int i){ return images_[i].filename(); }
    void push_back_order(std::pair <CurChangeType, int> a){   order_.push_back(a);  }
};

#endif // COLORCORRECTOR_H
