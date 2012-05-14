#include <iostream>
#include <QtGui>
#include "rsdmainwindow.h"

#include "vision/VisionSystem.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    RSDMainWindow w;
    w.resize(800,550);
    w.show();
    return a.exec();

    }


