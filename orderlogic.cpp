#include "orderlogic.h"
#include "vision/VisionSystem.h"
#include "serial/serialrobot.h"

orderlogic::orderlogic(QWidget *parent) :
    QWidget(parent)
{


}

void orderlogic::scanTable(){
    //define the robotframes:
    RF_11 = new Frame(VF_1pos + Xoff);
    RF_12 = new Frame(VF_2pos - VF_1pos + Xoff);

    RF_21 = new Frame(VF_2pos + Xoff);
    RF_22 = new Frame(VF_3pos - VF_2pos + Xoff);

    RF_31 = new Frame(VF_3pos + Xoff);
    RF_32 = new Frame(VF_4pos - VF_3pos + Xoff);

    RF_41 = new Frame(VF_4pos + Xoff);
    RF_42 = new Frame(gantryMax -VF_4pos + Xoff);

    //scanning first part:
    SerialRobot serial;
    serial.sendPLCcmd(VF_1pos,3);
    QTimer::singleShot(DELAY,this,SLOT(timedSC()));

    VisionSystem vs;
    //scan for bricks:

    vs.findBricks();
    brickBinning(vs.bricks, RF_11, RF_12);
    //move to next position:
    serial.sendPLCcmd(VF_2pos,3);
    QTimer::singleShot(DELAY,this,SLOT(timedSC()));

    vs.findBricks();
    brickBinning(vs.bricks, RF_21,RF_22);
    //next:

    serial.sendPLCcmd(VF_3pos,3);
    QTimer::singleShot(DELAY,this,SLOT(timedSC()));

    vs.findBricks();
    brickBinning(vs.bricks, RF_31,RF_32);
    //lastly:

    serial.sendPLCcmd(VF_4pos,3);
    QTimer::singleShot(DELAY,this,SLOT(timedSC()));

    vs.findBricks();
    brickBinning(vs.bricks, RF_41,RF_42);

    qDebug() << "Table scanned";

}

void orderlogic::brickBinning(std::vector<VisionSystem::Legobrick> bricks,  Frame *RF1, Frame *RF2){

    for (int i = 0; i < bricks.size(); i++){

        struct VisionSystem::Legobrick brick;

        brick.color = bricks[i].color;
        brick.orientation = bricks[i].orientation;
        brick.x = bricks[i].x;
        brick.y = bricks[i].y+Yoff; //note the offset!
        {
            if(bricks[i].x < Xbin){

                if(bricks[i].color == 0){
                    RF1->addBlue(brick);
                } else if(bricks[i].color == 1){
                    RF1->addRed(brick);
                } else if(bricks[i].color == 2){
                    RF1->addYellow(brick);
                }
            } else if(bricks[i].color >= Xbin){
                if(bricks[i].color == 0){
                    RF2->addBlue(brick);
                } else if(bricks[i].color == 1){
                    RF2->addRed(brick);
                } else if(bricks[i].color == 2){
                    RF2->addYellow(brick);
                }
            }
        }
    }

}

void orderlogic::timedSC(){
    qDebug()<< "Moving of gantry done!";
}
