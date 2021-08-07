#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Course project. Created by Oliynyk Volodymyr, PI-181");
    w.show();

    return a.exec();
}
