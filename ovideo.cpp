#include "ovideo.h"
#include <opencv2/videoio.hpp>

using namespace cv;

OVideo::OVideo() {}

QString OVideo::get_o(QString in, QString out, QString format){
    QString raw = in.mid(in.lastIndexOf('/')+1);
    raw = raw.left(raw.length()-4);
    raw.append('.');
    raw.append(format);
    out.append('/');
    out.append(raw);
    return out;
}

OVideo::OVideo(QString fname, QString path, QString format):filename_{fname},format_{format}, output_path_{get_o(fname,path,format)}{
}

int OVideo::fourcc()const{
    int r;
    if (format_ == "mp4")
        r = VideoWriter::fourcc('m','p', '4', 'v');
    else if (format_ == "wmv"){
        r = VideoWriter::fourcc('W', 'M', 'V', '1');
    }
    else if (format_ == "avi"){
        r = VideoWriter::fourcc('M', 'J', 'P', 'G');
    }
    else{
        r = VideoWriter::fourcc('m','p', '4', 'v');
    }
    return r;
}


