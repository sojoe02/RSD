#include "orderlogic.h"
#include "vision/VisionSystem.h"
#include "serial/serialrobot.h"
#include "vector"
#include <sstream>
#include <unistd.h>
#include <iostream>
#include "Globals.h"

orderlogic::orderlogic(QWidget *parent) :
    QWidget(parent)
{
    activeframe_ptr = 0;
    SerialRobot serial;
}

void orderlogic::resetSystem(){
    activeframe_ptr = 0;
}

void orderlogic::scanTable(){
    //initialize the robotframes, and calculate the positions:

    for(int i =0 ; i < no_frames; i++){
        frames.push_back(new Frame(FInterval*i));
    }
    //scanning each frame and putting in bricks the robot arms can reach:
    for(int j=0; j< no_frames; j++){
        serial.sendPLCcmd(FInterval*j,3);
        serial.sendPLCcmd(FInterval*j,3);
        qDebug() << FInterval * j;
        sleep(ScanDelay/1000);
        qDebug() << "wait done";

        VisionSystem vs;
        vs.findBricks();

        qDebug() << "bricks found: " << vs.bricks.size();

        Frame *fptr = frames[j];

        for (int i = 0; i < vs.bricks.size(); i++){


            if(vs.bricks[i].x*10 < 150){
                Legobrick brick;

                brick.color = vs.bricks[i].color;
                brick.orientation = vs.bricks[i].orientation;
                brick.x = 204 - vs.bricks[i].x * 10;
                brick.y = (vs.bricks[i].y*10) + Yoff; //note the offset!

                qDebug() << brick.x << vs.bricks[i].x;

                if(vs.bricks[i].color == 0){
                    fptr->addBlue(brick);
                } else if(vs.bricks[i].color == 1){
                    fptr->addRed(brick);
                } else if(vs.bricks[i].color == 2){
                    fptr->addYellow(brick);
                }
            }
        }
        std::cerr << fptr->toString() << std::endl;
    }

    serial.sendPLCcmd(0,3);
    serial.sendPLCcmd(0,3);


}


void orderlogic::makeFrame(int i){

}


void orderlogic::handleOrder(std::vector<int> orderarray){

    serial.sendPLCcmd(0,3);
    sleep(1);
    serial.sendPLCcmd(0,3);
    sleep(ScanDelay/1000 * 2);

    //pick blues:
    int k_blue = 0;
    int k_red = 0;
    int k_yellow = 0;

    for(int j= 0; j<frames.size() ; j++){

        qDebug() << "Moving to location " << FInterval*j + PickupOff;
        //take the brick!
        serial.sendPLCcmd(FInterval*j + PickupOff,3);
        sleep(1);
        serial.sendPLCcmd(FInterval*j + PickupOff,3);
        sleep(ScanDelay/1000);


        Frame *fptr = frames[j];
        std::cerr << fptr->toString() << std::endl;
        for(int i = k_blue; i < orderarray[0]; i++){

            Legobrick brick;
            brick = fptr->returnBlue();
            qDebug() << brick.x;
            if (brick.color != 3){
                qDebug() << "Picking up brick";
                std::stringstream string;
                string << ((int) brick.x);
                std::string x = string.str();
                x.insert(x.begin(), 3-x.size(), '0');
                string.str("");
                string << ((int) brick.y);
                std::string y = string.str();
                y.insert(y.begin(), 3-y.size(), '0');
                string.str("");
                string << ((155 - ((int) brick.orientation)) % 180);
                std::string orientation = string.str();
                orientation.insert(orientation.begin(), 3-orientation.size(), '0');
                string.str("");
                string << x << "," << y << "," << orientation << ",1";
                std::string stri = string.str();
                std::cerr << stri << std::endl;
                serial.sendRobotCoor(string.str());
                sleep(ScanDelay/1000);
                k_blue++;

            }
        }

        for(int i = k_red; i < orderarray[1]; i++){

            Legobrick brick;
            brick = fptr->returnRed();
            qDebug() << brick.x;
            if (brick.color != 3){
                qDebug() << "Picking up brick";
                std::stringstream string;
                string << ((int) brick.x);
                std::string x = string.str();
                x.insert(x.begin(), 3-x.size(), '0');
                string.str("");
                string << ((int) brick.y);
                std::string y = string.str();
                y.insert(y.begin(), 3-y.size(), '0');
                string.str("");
                string << ((155 - ((int) brick.orientation)) % 180);
                std::string orientation = string.str();
                orientation.insert(orientation.begin(), 3-orientation.size(), '0');
                string.str("");
                string << x << "," << y << "," << orientation << ",1";


                std::string stri = string.str();
                std::cerr << stri << std::endl;
                serial.sendRobotCoor(string.str());
                sleep(ScanDelay/1000);

                k_red++;

            }
        }

        for(int i = k_yellow; i < orderarray[2]; i++){
            Legobrick brick;
            brick = fptr->returnYellow();
            qDebug() << "picking up yellow " <<brick.x;
            if (brick.color != 3){
                qDebug() << "Picking up yellow brick";
                std::stringstream string;
                string << ((int) brick.x);
                std::string x = string.str();
                x.insert(x.begin(), 3-x.size(), '0');
                string.str("");
                string << ((int) brick.y);
                std::string y = string.str();
                y.insert(y.begin(), 3-y.size(), '0');
                string.str("");
                string << ((155 - ((int) brick.orientation)) % 180);
                std::string orientation = string.str();
                orientation.insert(orientation.begin(), 3-orientation.size(), '0');
                string.str("");
                string << x << "," << y << "," << orientation << ",1";
                std::string stri = string.str();
                std::cerr << stri << std::endl;
                serial.sendRobotCoor(string.str());
                sleep(ScanDelay/1000);
                k_yellow++;

            }
        }

        if(k_blue == orderarray[0] && k_red == orderarray[1] && k_yellow == orderarray[2]){
            emit orderdone();
            break;
        }

//        qDebug() << "Moving to next frame " << FInterval*j;
//        serial.sendPLCcmd(FInterval*j,3);
//        sleep(1);
//        serial.sendPLCcmd(FInterval*j,3);
//        sleep(ScanDelay/1000);

    }


}


void orderlogic::timedSC(){
    qDebug()<< "Moving of gantry done!";
}
