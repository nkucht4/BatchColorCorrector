#ifndef BATCHCC_H
#define BATCHCC_H

#include <QMainWindow>
#include "colorcorrector.h"
#include "currentpicture.h"
#include <QPixmap>

namespace Ui {
class Batchcc;
}

class Batchcc : public QMainWindow
{
    Q_OBJECT

public:
    explicit Batchcc(QWidget *parent = nullptr);
    ~Batchcc();

    void addNewItem(const QString& file, const int& i);
    QString getRawFilename(QString path);
    QPixmap filestr2pixmap(QString file);
    void centerticks();
    void updatePhoto();
    void displayNewPhoto();
    QString getOutputPath();
    void SaveImgWithChanges(ImgNode img, QString out_path);

public slots:
    void onOpenFile();
    void onListItemClicked(int index, int col = 0);
    void onRValChanged();
    void onBValChanged();
    void onGValChanged();
    void onHValChanged();
    void onSValChanged();
    void onVValChanged();
    void onLValChanged();

    void onOkR();
    void onOkG();
    void onOkB();
    void onOkH();
    void onOkS();
    void onOkV();
    void onOkL();

    void onSaveFiles();
    void onReset();
    void onPrev();
    void onNext();
private:
    Ui::Batchcc *ui;
    ColorCorrector CC;
    CurrentPicture displayed_pic;
    int c_index;
};

#endif // BATCHCC_H
