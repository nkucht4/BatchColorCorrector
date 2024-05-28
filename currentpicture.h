#ifndef CURRENTPICTURE_H
#define CURRENTPICTURE_H

#include <QString>
#include <QPixmap>
#include <opencv2/highgui.hpp>

enum class CurChangeType{
    R, G, B, H, S, V, L
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
    void Change(int);

    QString filename(){ return filename_;   }
    cv::Mat& mat(){  return mat_;    }
    QPixmap curmat2pixmap();

    void changeRGB(int val, int channel);
    void changeR(int val);
    void changeG(int val);
    void changeB(int val);

    void changeHSV(int val, int channel);
    void changeH(int val);
    void changeS(int val);
    void changeV(int val);
    void changeL(int val);

    bool OkPressed(CurChangeType type);

};

#endif // CURRENTPICTURE_H
