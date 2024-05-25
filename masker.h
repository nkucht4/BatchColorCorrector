#ifndef MASKER_H
#define MASKER_H

#include <opencv2/videoio.hpp>
#include <opencv2/video/background_segm.hpp>
#include <QMainWindow>
#include "ovideo.h"

namespace Ui {
class Masker;
}

class Masker : public QMainWindow
{
    Q_OBJECT

public:
    explicit Masker(QWidget *parent = nullptr);
    ~Masker();
    void show_progress();
    int handleError();
    void renderVideo(OVideo file_info);
    cv::Mat getMaskedMat(cv::Mat& imat, cv::BackgroundSubtractor& sub);

public slots:
    void onOpenFile(bool checked = false);
    void onConvert(bool checled = false);
    void onChoosePath(bool checked = false);


private:
    Ui::Masker *ui;
};

#endif // MASKER_H
