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
    //button.show();

    //test opencv shit:

       VisionSystem vs;



        cv::namedWindow("output", CV_WINDOW_NORMAL);

        vs.findBricks();


        //for (int i = 0; i < vs.bricks.size(); i++) {
        //    std::cout << vs.colors[vs.bricks[i].color] << " found at: [" << vs.bricks[i].x << "," << vs.bricks[i].y << "] - : " << vs.bricks[i].orientation << std::endl;
        //}



        cv::imshow("output", vs.outputImage);



        //cv::waitKey(0);
    return a.exec();

    }


