#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ovideo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show_progress();
    int handleError();
    void renderVideo(OVideo file_info);

public slots:
    void onOpenFile(bool checked = false);
    void onConvert(bool checled = false);
    void onChoosePath(bool checked = false);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
