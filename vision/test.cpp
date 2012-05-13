/*
 * test.cpp
 *
 *  Created on: Mar 12, 2012
 *      Author: rsdteam1
 */

#include "VisionSystem.h"
#include <stdio.h>
#include <iostream>

int main() {

	VisionSystem vs;


	cv::namedWindow("output", CV_WINDOW_NORMAL);

	vs.findBricks();


	for (int i = 0; i < vs.bricks.size(); i++) {
		std::cout << vs.colors[vs.bricks[i].color] << " found at: [" << vs.bricks[i].x << "," << vs.bricks[i].y << "] - ø: " << vs.bricks[i].orientation << std::endl;
	}



	cv::imshow("output", vs.outputImage);



	cv::waitKey(0);
	return 0;
}
