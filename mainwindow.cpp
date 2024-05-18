#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <opencv2/videoio.hpp>
#include "ovideo.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pB_openfile, &QPushButton::clicked, this, &MainWindow::onOpenFile);
    connect(ui->pB_path, &QPushButton::clicked, this, &MainWindow::onChoosePath);
    connect(ui->pB_convert, &QPushButton::clicked, this, &MainWindow::onConvert);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenFile(bool checked){
    QString filename_ = QFileDialog::getOpenFileName(this, tr("Choose a video to convert"), "C:\\", tr("Videos(*mov *wmv *mp4 *avi *mov"));
    ui->l_filename->setText(filename_);
}

void MainWindow::show_progress(){
    ui->progress->show();
    ui->progress->setText("In progress... Please, wait");
}

void MainWindow::onConvert(bool checked){
    if(!ui->l_error->isHidden()){
        ui->l_error->hide();
    }
    if (handleError()){
        return;
    }
    OVideo file_info{ui->l_filename->text(), ui->l_opath->text(), ui->pickFormat->currentText()};
    renderVideo(file_info);
    ui->progress->hide();
}

int MainWindow::handleError(){
    if (ui->l_filename->text() == "No file chosen"){
        ui->l_error->setText("Task failed. No video chosen");
        ui->l_error->show();
        return 1;
    }
    if (ui->pickFormat->currentText() == "Choose here" ){
        ui->l_error->setText("Task failed. No format chosen");
        ui->l_error->show();
        return 1;
    }
    if (ui->l_opath->text() == "No path chosen" || ui->l_opath->text().isEmpty()){
        ui->l_error->setText("Task failed. No ouput path chosen");
        ui->l_error->show();
        return 1;
    }
    return 0;
}

void MainWindow::renderVideo(OVideo file_info){
    show_progress();
    VideoCapture video{ui->l_filename->text().toStdString()};
    if (video.isOpened()){
        int frame_w = static_cast<int>(video.get(3));
        int frame_h = static_cast<int>(video.get(4));
        const int fps = 30;
        VideoWriter vidwriter{file_info.output_path(), file_info.fourcc(), fps, Size{frame_w, frame_h}};
        Mat cur_frame;
        for (;;){
            video >> cur_frame;
            if (cur_frame.empty())  break;
            vidwriter.write(cur_frame);
        }
    }
    else{
        ui->l_error->setText("Task failed. Video can't be opened");
        ui->l_error->show();
    }
}

void MainWindow::onChoosePath(bool checked)
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Choose an output directory"), "C:\\");
    ui->l_opath->setText(path);
}

