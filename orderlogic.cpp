#include "orderlogic.h"
#include "vision/VisionSystem.h"
#include "serial/serialrobot.h"
#include "vector"

orderlogic::orderlogic(QWidget *parent) :
    QWidget(parent)
{
    activeframe_ptr = 0;
}

void orderlogic::resetSystem(){
    activeframe_ptr = 0;
}

void orderlogic::scanTable(){
    //initialize the robotframes, and calculate the positions:

    for(int i =0 ; i < FInterval; i++){
        frames.push_back(new Frame(FInterval));
    }
    //scanning each frame and putting in bricks the robot arms can reach:
    SerialRobot serial;
    VisionSystem vs;

    for(int i=0; i< FInterval; i++){
        serial.sendPLCcmd(FInterval*i,3);
        QTimer::singleShot(DELAY,this,SLOT(timedSC()));
        vs.findBricks();

        for (int i = 0; i < vs.bricks.size(); i++){

            struct VisionSystem::Legobrick brick;

            brick.color = vs.bricks[i].color;
            brick.orientation = vs.bricks[i].orientation;
            brick.x = vs.bricks[i].x+Xoff;
            brick.y = vs.bricks[i].y+Yoff; //note the offset!

            if(vs.bricks[i].color == 0){
                frames[i]->addBlue(brick);
            } else if(vs.bricks[i].color == 1){
                frames[i]->addRed(brick);
            } else if(vs.bricks[i].color == 2){
                frames[i]->addYellow(brick);
            }

        }
    }

}

void orderlogic::handleOrder(std::vector<int> orderarray){

    SerialRobot serial;
    //pick blues:
    for(int i = 0; i < orderarray[i]; i++){
        Frame *fptr = frames[activeframe_ptr];
        VisionSystem::Legobrick brick = fptr->returnBlue();
        if (brick.color == 3){
            activeframe_ptr++;
            fptr = frames[activeframe_ptr];
            serial.sendPLCcmd(fptr->getPosition()+Roff,3);
            QTimer::singleShot(DELAY,this,SLOT(timedSC()));
        } else{
            //serial.sendRobotCoor(...);
        }

    }
    //pick reds:
    for(int i = 0; i < orderarray[i]; i++){
        Frame *fptr = frames[activeframe_ptr];
        VisionSystem::Legobrick brick = fptr->returnRed();
        if (brick.color == 3){
            activeframe_ptr++;
            fptr = frames[activeframe_ptr];
            serial.sendPLCcmd(fptr->getPosition()+Roff,3);
            QTimer::singleShot(DELAY,this,SLOT(timedSC()));
        } else{
            //serial.sendRobotCoor(...);
        }
    }
    //pick yellows:
    for(int i = 0; i < orderarray[i]; i++){
        Frame *fptr = frames[activeframe_ptr];
        VisionSystem::Legobrick brick = fptr->returnYellow();
        if (brick.color == 3){
            activeframe_ptr++;
            fptr = frames[activeframe_ptr];
            serial.sendPLCcmd(fptr->getPosition()+Roff,3);
            QTimer::singleShot(DELAY,this,SLOT(timedSC()));
        } else{
            //serial.sendRobotCoor(...);
        }
    }
}


void orderlogic::timedSC(){
    qDebug()<< "Moving of gantry done!";
}
