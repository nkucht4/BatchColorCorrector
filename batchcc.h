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

public slots:
    void onOpenFile();
    void onListItemClicked(int index, int col = 0);
    void onRValChanged();
    void onBValChanged();
    void onGValChanged();

private:
    Ui::Batchcc *ui;
    ColorCorrector CC;
    CurrentPicture displayed_pic;
};

#endif // BATCHCC_H
