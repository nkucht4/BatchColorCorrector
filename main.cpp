#include "batchcc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Batchcc window;
    window.show();
    return a.exec();
}
