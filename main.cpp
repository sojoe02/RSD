#include <iostream>
#include <QtGui>
#include "rsdmainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    RSDMainWindow w;
    w.resize(800,500);
    w.show();
    //button.show();

    return a.exec();
}

