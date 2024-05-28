#include "batchcc.h"
#include "ui_batchcc.h"
#include "QFileDialog"

Batchcc::Batchcc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Batchcc)
{
    ui->setupUi(this);
    centerticks();
    PrepareEmpty();

    connect(ui->pB_addphotos, &QPushButton::pressed, this, &Batchcc::onOpenFile);
    connect(ui->t_photos, &QTableWidget::cellClicked, this, &Batchcc::onListItemClicked);
    connect(ui->pb_save, &QPushButton::pressed, this, &Batchcc::onSaveFiles);
    connect(ui->pb_reset, &QPushButton::pressed, this, &Batchcc::onReset);
    connect(ui->pB_prev, &QPushButton::pressed, this, &Batchcc::onPrev);
    connect(ui->pB_next, &QPushButton::pressed, this, &Batchcc::onNext);
    connect(ui->pb_delete, &QPushButton::pressed, this, &Batchcc::onDelete);

    connect(ui->slid_r, &QSlider::sliderReleased, this, &Batchcc::onRValChanged);
    connect(ui->slid_g, &QSlider::sliderReleased, this, &Batchcc::onGValChanged);
    connect(ui->slid_b, &QSlider::sliderReleased, this, &Batchcc::onBValChanged);
    connect(ui->slid_h, &QSlider::sliderReleased, this, &Batchcc::onHValChanged);
    connect(ui->slid_s, &QSlider::sliderReleased, this, &Batchcc::onSValChanged);
    connect(ui->slid_v, &QSlider::sliderReleased, this, &Batchcc::onVValChanged);
    connect(ui->slid_l, &QSlider::sliderReleased, this, &Batchcc::onLValChanged);

    connect(ui->pb_r, &QPushButton::pressed, this, &Batchcc::onOkR);
    connect(ui->pb_g, &QPushButton::pressed, this, &Batchcc::onOkG);
    connect(ui->pb_b, &QPushButton::pressed, this, &Batchcc::onOkB);
    connect(ui->pb_h, &QPushButton::pressed, this, &Batchcc::onOkH);
    connect(ui->pb_s, &QPushButton::pressed, this, &Batchcc::onOkS);
    connect(ui->pb_v, &QPushButton::pressed, this, &Batchcc::onOkV);
    connect(ui->pb_l, &QPushButton::pressed, this, &Batchcc::onOkL);
}

Batchcc::~Batchcc()
{
    delete ui;
}

void Batchcc::onOpenFile(){
    QStringList filenames = QFileDialog::getOpenFileNames(this, tr("Pick image(s) to edit"), "C:\\", tr("Images (*.png *.xpm *.jpg)"));
    if (filenames.isEmpty()){
        return;
    }
    int i = ui->t_photos->rowCount();
    ui->t_photos->setRowCount(ui->t_photos->rowCount() + filenames.count());
    int isFirst = i;
    for (const auto &file : filenames){
        CC.push_back({file});
        addNewItem(file, i);
        i++;
    }
    if (isFirst == 0){
        onListItemClicked(0, 0);
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
    displayed_pic.Change(CC.filename_at(index),ui->ImgDisplay->pixmap());
    c_index = index;
    if (CC.orderVec().empty()){
        ui->ImgDisplay->setPixmap((QPixmap{filestr2pixmap(CC.filename_at(index))}).scaled({691,451}, Qt::KeepAspectRatio));
    }
    else{
        displayNewPhoto();
    }
    ui->l_iname->setText(getRawFilename(CC.filename_at(index)));
}

void Batchcc::centerticks(){
    ui->ImgDisplay->setAlignment(Qt::AlignCenter);
    ui->slid_r->setRange(-100,100);
    ui->slid_r->setValue(0);
    ui->slid_g->setRange(-100,100);
    ui->slid_g->setValue(0);
    ui->slid_b->setRange(-100,100);
    ui->slid_b->setValue(0);
    ui->slid_h->setRange(-100,100);
    ui->slid_h->setValue(0);
    ui->slid_s->setRange(-150,150);
    ui->slid_s->setValue(0);
    ui->slid_v->setRange(-100,100);
    ui->slid_v->setValue(0);
    ui->slid_l->setRange(-100,100);
    ui->slid_l->setValue(0);
}

void Batchcc::onRValChanged(){
    displayed_pic.changeR(ui->slid_r->value());
    updatePhoto();
}

void Batchcc::onBValChanged(){
    displayed_pic.changeB(ui->slid_b->value());
    updatePhoto();
}

void Batchcc::onGValChanged(){
    displayed_pic.changeG(ui->slid_g->value());
    updatePhoto();
}

void Batchcc::onHValChanged(){
    displayed_pic.changeH(ui->slid_h->value());
    updatePhoto();
}

void Batchcc::onSValChanged(){
    displayed_pic.changeS(ui->slid_s->value());
    updatePhoto();
}

void Batchcc::onVValChanged(){
    displayed_pic.changeV(ui->slid_v->value());
    updatePhoto();
}

void Batchcc::onLValChanged(){
    displayed_pic.changeL(ui->slid_l->value());
    updatePhoto();
}

void Batchcc::onOkR(){
    if (displayed_pic.OkPressed(CurChangeType::R)){
        CC.push_back_order(std::make_pair(CurChangeType::R, ui->slid_r->value()));
        CC.props().r = ui->slid_r->value();
    }
}

void Batchcc::onOkB(){
    if (displayed_pic.OkPressed(CurChangeType::B)){
        CC.push_back_order(std::make_pair(CurChangeType::B, ui->slid_b->value()));
       CC.props().b = ui->slid_b->value();
    }
}

void Batchcc::onOkG(){
    if (displayed_pic.OkPressed(CurChangeType::G)){
        CC.push_back_order(std::make_pair(CurChangeType::G, ui->slid_g->value()));
        CC.props().g = ui->slid_g->value();
    }
}

void Batchcc::onOkH(){
    if (displayed_pic.OkPressed(CurChangeType::H)){
        CC.push_back_order(std::make_pair(CurChangeType::H, ui->slid_h->value()));
        CC.props().h = ui->slid_h->value();
    }
}

void Batchcc::onOkS(){
    if (displayed_pic.OkPressed(CurChangeType::S)){
        CC.push_back_order(std::make_pair(CurChangeType::S, ui->slid_s->value()));
        CC.props().s = ui->slid_s->value();
    }
}

void Batchcc::onOkV(){
    if (displayed_pic.OkPressed(CurChangeType::V)){
        CC.push_back_order(std::make_pair(CurChangeType::V, ui->slid_v->value()));
        CC.props().v = ui->slid_v->value();
    }
}

void Batchcc::onOkL(){
    if (displayed_pic.OkPressed(CurChangeType::L)){
        CC.push_back_order(std::make_pair(CurChangeType::L, ui->slid_l->value()));
        CC.props().l = ui->slid_l->value();
    }
}

void Batchcc::updatePhoto(){
    ui->ImgDisplay->setPixmap(displayed_pic.curmat2pixmap().scaled({691,451}, Qt::KeepAspectRatio));
}

void Batchcc::displayNewPhoto(){
   for (auto state : CC.orderVec()){
        switch (state.first){
        case CurChangeType::R:
            displayed_pic.changeR(CC.props().r);
            displayed_pic.OkPressed(CurChangeType::R);
            break;
        case CurChangeType::B:
            displayed_pic.changeB(CC.props().b);
            displayed_pic.OkPressed(CurChangeType::B);
            break;
        case CurChangeType::G:
            displayed_pic.changeG(CC.props().g);
            displayed_pic.OkPressed(CurChangeType::G);
            break;
        case CurChangeType::H:
            displayed_pic.changeH(CC.props().h);
            displayed_pic.OkPressed(CurChangeType::H);
            break;
        case CurChangeType::S:
            displayed_pic.changeS(CC.props().s);
            displayed_pic.OkPressed(CurChangeType::S);
            break;
        case CurChangeType::V:
            displayed_pic.changeV(CC.props().v);
            displayed_pic.OkPressed(CurChangeType::V);
            break;
        case CurChangeType::L:
            displayed_pic.changeV(CC.props().l);
            displayed_pic.OkPressed(CurChangeType::L);
            break;
        }
    }
   updatePhoto();
}

void Batchcc::onSaveFiles(){
    QString opath {getOutputPath()};
    if (opath.isEmpty()){
        return;
    }
    for (auto img : CC.img_vec()){
        SaveImgWithChanges(img, opath);
    }
    return;
}

QString Batchcc::getOutputPath(){
    return QFileDialog::getExistingDirectory(this, tr("Choose the output directory"), "C:\\");
}

void Batchcc::SaveImgWithChanges(ImgNode image, QString out_path){
    CurrentPicture processed_picture{image.filename(), filestr2pixmap(image.filename())};
    for (auto state : CC.orderVec()){
        switch (state.first){
        case CurChangeType::R:
            processed_picture.changeR(CC.props().r);
            processed_picture.OkPressed(CurChangeType::R);
            break;
        case CurChangeType::B:
            processed_picture.changeB(CC.props().b);
            processed_picture.OkPressed(CurChangeType::B);
            break;
        case CurChangeType::G:
            processed_picture.changeG(CC.props().g);
            processed_picture.OkPressed(CurChangeType::G);
            break;
        case CurChangeType::H:
            processed_picture.changeH(CC.props().h);
            processed_picture.OkPressed(CurChangeType::H);
            break;
        case CurChangeType::S:
            processed_picture.changeS(CC.props().s);
            processed_picture.OkPressed(CurChangeType::S);
            break;
        case CurChangeType::V:
            processed_picture.changeV(CC.props().v);
            processed_picture.OkPressed(CurChangeType::V);
            break;
        case CurChangeType::L:
            processed_picture.changeV(CC.props().l);
            processed_picture.OkPressed(CurChangeType::L);
            break;
        }
    }
    out_path = out_path + "/BCC" + getRawFilename(image.filename());
    cv::imwrite(out_path.toStdString(), processed_picture.mat());
}

void Batchcc::onReset(){
    CC.clearOrder();
    if (!CC.img_vec().empty()){
        displayed_pic.Change(displayed_pic.filename(), filestr2pixmap(displayed_pic.filename()));
        ui->ImgDisplay->setPixmap((QPixmap{filestr2pixmap(displayed_pic.filename())}).scaled({691,451}, Qt::KeepAspectRatio));
    }
    centerticks();
}

void Batchcc::onPrev(){
    if (CC.img_vec().empty()){
        return;
    }
    if (c_index == 0){
        onListItemClicked(CC.img_vec().size() - 1, 0);
    }
    else{
        onListItemClicked(c_index - 1, 0);
    }
}

void Batchcc::onNext(){
    if (CC.img_vec().empty()){
        return;
    }
    if (c_index == CC.img_vec().size() - 1){
        onListItemClicked(0, 0);
    }
    else{
        onListItemClicked(c_index + 1, 0);
    }
}

void Batchcc::onDelete(){
    if (CC.img_vec().empty()){
        return;
    }
    CC.img_vec().erase(CC.img_vec().begin() + c_index);
    if (CC.img_vec().empty()){
        PrepareEmpty();
    }
    else if (c_index == CC.img_vec().size()){
        onListItemClicked(c_index - 1, 0);
        delete ui->t_photos->item(ui->t_photos->rowCount(), 0);
        ui->t_photos->setRowCount(ui->t_photos->rowCount()-1);
        return;
    }
    else{
        onListItemClicked(c_index, 0);
    }
    for (int i = c_index; i < ui->t_photos->rowCount()-1; i++){
        delete ui->t_photos->item(i, 0);
        ui->t_photos->setItem(i, 0, new QTableWidgetItem{ui->t_photos->item(i+1,0)->text()});
        ui->t_photos->item(i, 0)->setIcon(ui->t_photos->item(i+1,0)->icon());
    }
    delete ui->t_photos->item(ui->t_photos->rowCount(), 0);
    ui->t_photos->setRowCount(ui->t_photos->rowCount()-1);
}

void Batchcc::PrepareEmpty(){
    ui->ImgDisplay->setPixmap(QPixmap{":/img/black.png"});
    displayed_pic.Change(0);
}
