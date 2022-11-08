#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setStyleSheet("background-color: rgb(71, 84, 83);");
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
