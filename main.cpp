#include "mainwindow.hpp"
#include <QApplication>
#include <libnova/libnova.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
