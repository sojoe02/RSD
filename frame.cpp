#include "frame.h"
#include <QVector>
#include <vision/VisionSystem.h>

Frame::Frame(int position):
    position(position)
{


    nobrick.color=4;
    nobrick.orientation= 0;
    nobrick.x = 0;
    nobrick.y = 0;

}

void Frame::addBlue(VisionSystem::Legobrick brick){
    blues.push_back(brick);
}

void Frame::addYellow(VisionSystem::Legobrick brick){
    yellows.push_back(brick);
}

void Frame::addRed(VisionSystem::Legobrick brick){
    reds.push_back(brick);
}

VisionSystem::Legobrick Frame::returnBlue(){
    if(blues.empty()){
        return nobrick;
    }
    VisionSystem::Legobrick brick = blues.back();
    blues.pop_back();
    return brick;

}

VisionSystem::Legobrick Frame::returnRed(){
    if(reds.empty()){
        return nobrick;
    }
    VisionSystem::Legobrick brick =  reds.back();
    reds.pop_back();
    return brick;
}

VisionSystem::Legobrick Frame::returnYellow(){
    if(blues.empty()){
        return nobrick;
    }
    VisionSystem::Legobrick brick = yellows.back();
    yellows.pop_back();
    return brick;
}

int Frame:: getPosition(){
    return position;
}
