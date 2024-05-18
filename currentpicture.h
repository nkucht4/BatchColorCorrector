#ifndef CURRENTPICTURE_H
#define CURRENTPICTURE_H

#include <QString>
#include <QPixmap>
#include <opencv2/highgui.hpp>

enum class CurChangeType{
    R, G, B, H, S, L
};

class CurrentPicture
{
    QString filename_;
    QPixmap pixmap_;
    cv::Mat mat_;
    cv::Mat current_mat;
    CurChangeType ctype;

public:
    CurrentPicture(){}
    CurrentPicture(QString fname, QPixmap pmap);

    void Change(QString filenane, QPixmap map);

    QString filename(){ return filename_;   }
    QPixmap pixmap(){   return pixmap_; }
    cv::Mat mat(){  return mat_;    }

    void changeRGB(int val, int channel);
    void changeR(int val);
    void changeG(int val);
    void changeB(int val);

};

#endif // CURRENTPICTURE_H
