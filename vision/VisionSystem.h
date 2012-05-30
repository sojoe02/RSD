/*
 * VisionSystem.h
 *
 *  Created on: Mar 12, 2012
 *      Author: rsdteam1
 */
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include "Globals.h"

using std::string;

#ifndef VISIONSYSTEM_H_
#define VISIONSYSTEM_H_

class VisionSystem {

private:
    int dist(cv::Point a, cv::Point b) {
        return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
    }
    double settings[3][4];
    double pixelsPerCmX;
    double pixelsPerCmY;

    CvCapture* capture;


public:

    string colors[3];

    std::vector<Legobrick> bricks;
    cv::Mat outputImage;

    VisionSystem() {
       capture = cvCaptureFromCAM(CV_CAP_ANY);
       cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);
       cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);
       if ( !capture ) {
         //error
       }

       pixelsPerCmX = 15.48;
       pixelsPerCmY = 15.80;

       settings[0][0] = 15.;
       settings[0][1] = 13.;
       settings[0][2] = 0.02;
       settings[0][3] = 70.;
       settings[1][0] = 15.;
       settings[1][1] = 15.;
       settings[1][2] = 0.04;
       settings[1][3] = 100.;
       settings[2][0] = 15.;
       settings[2][1] = 15.;
       settings[2][2] = 0.04;
       settings[2][3] = 150.;

       colors[0] = "blue";
       colors[1] = "red";
       colors[2] = "yellow";
    }

    bool findBricks();
};


#endif //VISIONSYSTEM_H_
