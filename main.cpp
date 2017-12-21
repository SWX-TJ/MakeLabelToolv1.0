#include "mainwindow.h"
#include <QApplication>
#include "selectlabelmodelmainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SelectLabelModelMainWindow w;
    w.show();
    //MainWindow w;
    //w.show();

    return a.exec();
}
