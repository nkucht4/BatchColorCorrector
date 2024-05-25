#include "menu.h"
#include "mainwindow.h"
#include "batchcc.h"
#include "masker.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Menu w;
    //w.show();
    //MainWindow converter_window;
    //converter_window.show();
    //Batchcc cc_edit_window;
    //cc_edit_window.show();
    Masker masker_window;
    masker_window.show();
    return a.exec();
}
