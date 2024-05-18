#ifndef OVIDEO_H
#define OVIDEO_H
#include <qstring.h>

class OVideo
{
private:
    QString filename_;
    QString format_;
    QString output_path_;

public:
    OVideo();
    OVideo(QString fname, QString path, QString format);

    std::string filename()const{ return filename_.toStdString(); }
    QString get_o(QString in , QString out, QString format);
    std::string output_path()const{ return output_path_.toStdString();  }
    QString format()const{  return format_; }
    int fourcc()const;

};

#endif // OVIDEO_H
