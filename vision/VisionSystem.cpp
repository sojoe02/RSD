/*
 * TestCam.cpp
 *
 *  Created on: Feb 15, 2012
 *      Author: rsdteam1
 */

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <iostream>
#include "VisionSystem.h"
#include "time.h"


     // A Simple Camera Capture Framework
bool VisionSystem::findBricks() {
         int i = 0;
       while ( i < 10 ) {
          i++;
         // Get one frame
         IplImage* frame = cvQueryFrame( capture );
         if ( !frame ) {
           fprintf( stderr, "ERROR: frame is null...\n" );
           getchar();
           break;
         }

         cv::Mat ref = frame;
         cv::Mat org;


         cv::cvtColor(ref, org, CV_RGB2HSV);

         cv::Mat segmented = cv::Mat().zeros(org.rows, org.cols, CV_8UC1);
         cv::Mat output = cv::Mat(org.rows, org.cols, CV_8UC3);

         //segmentation

         cv::Mat tmp = cv::Mat().zeros(org.rows, org.cols, CV_8UC1);
         cv::inRange(org, cv::Scalar(111, 50, 50), cv::Scalar(121, 255, 255), tmp); //red
         segmented = segmented + tmp;
         cv::inRange(org, cv::Scalar(0, 10, 10), cv::Scalar(10, 255, 255), tmp); //blue
         segmented = segmented + tmp;
         cv::inRange(org, cv::Scalar(130, 10, 10), cv::Scalar(180, 255, 255), tmp); //blue2
         segmented = segmented + tmp;
         cv::inRange(org, cv::Scalar(95, 50, 210), cv::Scalar(107, 255, 255), tmp); //yellow
         segmented = segmented + tmp;



         //CCA

         segmented.copyTo(tmp);
         segmented.zeros(segmented.rows, segmented.cols, CV_8UC1);
         cv::Mat dsts;

         std::vector< std::vector<cv::Point> > contours;
         std::vector< std::vector<cv::Point> > newcontours;

         cv::findContours(tmp, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

         //Find bricks with area bigger than 600
         for (int i = 0; i < contours.size(); i++) {
             if (cv::contourArea(cv::Mat(contours[i])) > 300.0) {
                 newcontours.push_back(contours[i]);
             }
         }

         std::vector<cv::Point> corners;

         //Draw each brick in an image, and send it on.
         bricks.clear();
         for (int p = 0; p < newcontours.size(); p++) {

             int smallestx = org.rows;
             int smallesty = org.cols;

             for (int l = 0; l < newcontours[p].size(); l++) {
                 if (newcontours[p][l].x < smallestx) {
                     smallestx = newcontours[p][l].x;
                 }
                 if (newcontours[p][l].y < smallesty) {
                     smallesty = newcontours[p][l].y;
                 }
             }

             dsts = cv::Mat().zeros(org.rows, org.cols, CV_8UC1);
             cv::drawContours(dsts, newcontours, p, cv::Scalar(255,255,255), CV_FILLED, 8);
             segmented = segmented + dsts;

             cv::Mat dst = cv::Mat().zeros(org.rows, org.cols, CV_32FC1);

             //Do corner detection

             int c;

             int area = cv::contourArea(cv::Mat(newcontours[p]));
             if (area > 300 && area < 1000) {
                 c = 0;
             } else if (area > 1000 && area < 1600) {
                 c = 1;
             } else {
                 c = 2;
             }

             if (smallestx+100 >= org.cols || smallesty+100 >= org.rows || smallestx-10 <= 0 || smallesty-10 <= 0) {
                 //error
                 break;
             }
             cv::Mat smaller = dsts.rowRange(cv::Range(smallesty-10, smallesty+100));
             smaller = smaller.colRange(cv::Range(smallestx-10, smallestx+100));

             cv::cornerHarris(smaller, dst, settings[c][0], settings[c][1], settings[c][2]);

             cv::normalize(dst, dst, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());



             bool add = true;

             for (int j = 0; j < dst.rows; j++) {
                 for (int i = 0; i < dst.cols; i++) {
                     if ((int) dst.at<float>(j,i) > settings[c][3]) {
                         if (corners.empty()) {
                             corners.push_back(cv::Point(smallestx+i-10,smallesty+j-10));
                         }
                         for (int k = 0; k < corners.size(); k++) {
                             double dist = sqrt(pow(corners[k].x-(i+smallestx-10),2)+pow(corners[k].y-(j+smallesty-10),2));
                             if (dist < 15) {
                                 add = false;
                             }
                         }
                         if (add) {
                             corners.push_back(cv::Point(smallestx+i-10,smallesty+j-10));
                         }
                     }
                     add = true;
                 }
             }



             //Find average (center)
             double x = 0, y = 0;

             int kl = corners.size();
             //std::cout << kl << std::endl;
             int mindistidx = 1;

             for (int i = 0; i < corners.size(); i++) {
                 cv::circle(segmented, cv::Point(corners[i].x,corners[i].y), 3, cv::Scalar(128,128,128));

                 x += corners[i].x/((double) corners.size());
                 y += corners[i].y/((double) corners.size());
                 if (i > 1) {
                     if (dist(corners[0], corners[i]) < dist(corners[0],corners[mindistidx])) {
                         mindistidx = i;
                     }
                 }
             }

             int middlex = (corners[0].x + corners[mindistidx].x)/2;
             int middley = (corners[0].y + corners[mindistidx].y)/2;

             cv::circle(segmented, cv::Point(x,y), 3, cv::Scalar(128,128,128));
             cv::line(segmented, cv::Point(middlex, middley), cv::Point(x,y), cv::Scalar(200,200,200));
             double a = (middley-y)/((double) middlex-x);

             double angle = atan(a) * 180/M_PI;

             bricks.push_back({abs(angle), (segmented.cols-x)/pixelsPerCmX, (segmented.rows-y)/pixelsPerCmY, c});

             corners.clear();
         }



         outputImage = segmented;

         // Have a small delay
         cv::waitKey(1);
       }
       // Release the capture device housekeeping
       cvReleaseCapture( &capture );
       cvDestroyWindow( "Org" );
       cvDestroyWindow( "Yellow" );
       cvDestroyWindow( "Blue" );
       cvDestroyWindow( "Red" );
       return 0;
     }
