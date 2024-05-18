#include "batchcc.h"
#include "ui_batchcc.h"
#include "QFileDialog"
#include <iostream>

Batchcc::Batchcc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Batchcc)
{
    ui->setupUi(this);
    centerticks();

    connect(ui->pB_addphotos, &QPushButton::pressed, this, &Batchcc::onOpenFile);
    connect(ui->t_photos, &QTableWidget::cellClicked, this, &Batchcc::onListItemClicked);

    connect(ui->slid_r, &QSlider::sliderReleased, this, &Batchcc::onRValChanged);
    connect(ui->slid_g, &QSlider::sliderReleased, this, &Batchcc::onGValChanged);
    connect(ui->slid_b, &QSlider::sliderReleased, this, &Batchcc::onBValChanged);
}

Batchcc::~Batchcc()
{
    delete ui;
}

void Batchcc::onOpenFile(){
    QStringList filenames = QFileDialog::getOpenFileNames(this, tr("Pick image(s) to edit"), "C:\\", tr("Images (*.png *.xpm *.jpg)"));
    int i = ui->t_photos->rowCount();
    ui->t_photos->setRowCount(ui->t_photos->rowCount() + filenames.count());
    for (const auto &file : filenames){
        CC.push_back({file});
        addNewItem(file, i);
        i++;
    }
}

void Batchcc::addNewItem(const QString& file, const int& i){
    ui->t_photos->setItem(i, 0, new QTableWidgetItem{getRawFilename(file)});
    QIcon thumbnail(QPixmap{filestr2pixmap(file)});
    ui->t_photos->item(i, 0)->setIcon(thumbnail);
}

QPixmap Batchcc::filestr2pixmap(QString file){
    QFile img_tn{file};
    img_tn.open(QIODevice::ReadOnly);
    QByteArray imgData = img_tn.readAll();
    QPixmap pixmap;
    pixmap.loadFromData(imgData);
    return pixmap;
}

QString Batchcc::getRawFilename(QString path){
    return path.mid(path.lastIndexOf('/')+1);
}

void Batchcc::onListItemClicked(int index, int col){
    ui->ImgDisplay->setPixmap((QPixmap{filestr2pixmap(CC.filename_at(index))}).scaled({691,451}, Qt::KeepAspectRatio));
    ui->ImgDisplay->setAlignment(Qt::AlignHCenter);
    displayed_pic.Change(CC.filename_at(index),ui->ImgDisplay->pixmap());
}

void Batchcc::centerticks(){
    ui->slid_r->setRange(-50,50);
    ui->slid_r->setValue(0);
    ui->slid_g->setRange(-50,50);
    ui->slid_g->setValue(0);
    ui->slid_b->setRange(-50,50);
    ui->slid_b->setValue(0);
}

void Batchcc::onRValChanged(){
    std::cout<<"B"<<std::endl;
    displayed_pic.changeR(ui->slid_r->value());
}

void Batchcc::onBValChanged(){
    displayed_pic.changeB(ui->slid_r->value());
}

void Batchcc::onGValChanged(){
    displayed_pic.changeG(ui->slid_r->value());
}
