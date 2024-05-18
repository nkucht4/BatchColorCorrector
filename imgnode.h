#ifndef IMGNODE_H
#define IMGNODE_H
#include "QString"

class ImgNode
{
    QString filename_;
public:
    ImgNode(QString filename);

    QString filename(){ return filename_;   }
};

#endif // IMGNODE_H
