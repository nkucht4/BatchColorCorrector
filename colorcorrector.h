#ifndef COLORCORRECTOR_H
#define COLORCORRECTOR_H
#include <vector>
#include "imgnode.h"
#include <QString>
#include "currentpicture.h"

struct Properties{
    int r = 0;
    int g = 0;
    int b = 0;
    int h = 0;
    int s = 0;
    int v = 0;
    int l = 0;
};

class ColorCorrector
{
    Properties props_;
    std::vector <ImgNode> images_;
    std::vector <std::pair <CurChangeType, int>> order_;
public:
    ColorCorrector();

    void push_back(ImgNode new_element){    images_.push_back(new_element); }
    QString filename_at(int i){ return images_[i].filename(); }
    void push_back_order(std::pair <CurChangeType, int> a){   order_.push_back(a);  }
    std::vector<std::pair <CurChangeType, int>> orderVec(){  return order_; }
    Properties& props(){ return props_;  }
    std::vector <ImgNode>& img_vec(){   return images_; }
    void clearOrder(){  order_.clear(); }
    void eraseImg(int index){   images_.erase(images_.begin() + index);   }
};

#endif // COLORCORRECTOR_H
