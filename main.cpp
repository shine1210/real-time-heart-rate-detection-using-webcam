#include "mainthread.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainThread w;
    w.setWindowTitle("HeartRate");
    w.show();

    return a.exec();
}
