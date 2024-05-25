#include "masker.h"
#include "ui_masker.h"

#include <QFileDialog>

using namespace cv;

Masker::Masker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Masker)
{
    ui->setupUi(this);

    connect(ui->pB_openfile, &QPushButton::clicked, this, &Masker::onOpenFile);
    connect(ui->pB_path, &QPushButton::clicked, this, &Masker::onChoosePath);
    connect(ui->pB_convert, &QPushButton::clicked, this, &Masker::onConvert);
}

Masker::~Masker()
{
    delete ui;
}

void Masker::onOpenFile(bool checked){
    QString filename_ = QFileDialog::getOpenFileName(this, tr("Choose a video to convert"), "C:\\", tr("Videos(*mov *wmv *mp4 *avi *mov"));
    ui->l_filename->setText(filename_);
}

void Masker::onChoosePath(bool checked)
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Choose the output directory"), "C:\\");
    ui->l_opath->setText(path);
}

void Masker::onConvert(bool checked){
    if(!ui->l_error->isHidden()){
        ui->l_error->hide();
        this->repaint();
    }
    if (handleError()){
        return;
    }
    OVideo file_info{ui->l_filename->text(), ui->l_opath->text(), ui->pickFormat->currentText()};
    renderVideo(file_info);
    ui->progress->hide();
    this->repaint();
}

int Masker::handleError(){
    if (ui->l_filename->text() == "No file chosen"){
        ui->l_error->setText("Task failed. No video chosen");
        ui->l_error->show();
        this->repaint();
        return 1;
    }
    if (ui->pickFormat->currentText() == "Choose here" ){
        ui->l_error->setText("Task failed. No format chosen");
        ui->l_error->show();
        this->repaint();
        return 1;
    }
    if (ui->l_opath->text() == "No path chosen" || ui->l_opath->text().isEmpty()){
        ui->l_error->setText("Task failed. No ouput path chosen");
        ui->l_error->show();
        this->repaint();
        return 1;
    }
    return 0;
}

void Masker::renderVideo(OVideo file_info){
    show_progress();
    VideoCapture video{ui->l_filename->text().toStdString()};
    if (video.isOpened()){
        VideoWriter vidwriter{file_info.output_path(), file_info.fourcc(), video.get(CAP_PROP_FPS), Size{static_cast<int>(video.get(3)), static_cast<int>(video.get(4))}};
        Mat cur_frame;
        BackgroundSubtractor* sub;
        sub = createBackgroundSubtractorMOG2();
        for (;;){
            video >> cur_frame;
            if (cur_frame.empty())  break;
            vidwriter.write(cur_frame);
        }
    }
    else{
        ui->l_error->setText("Task failed. Video can't be opened");
        ui->l_error->show();
        this->repaint();
    }
}

void Masker::show_progress(){
    ui->progress->show();
    ui->progress->setText("In progress... Please, wait");
    this->repaint();
}

cv::Mat Masker::getMaskedMat(cv::Mat& imat, cv::BackgroundSubtractor& sub){

}

