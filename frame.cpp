#include "frame.h"
#include <QVector>
#include <vision/VisionSystem.h>
#include <vector>
#include <Globals.h>
#include <iostream>

Frame::Frame(int position):
    position(position)
{

    nobrick.color = 3;
    nobrick.orientation= 0;
    nobrick.x = 0;
    nobrick.y = 0;
}

void Frame::addBlue(Legobrick brick){
    Legobrick thisbrick = brick;
    blues.push_back(thisbrick);
}

void Frame::addYellow(Legobrick brick){
    Legobrick thisbrick = brick;
    yellows.push_back(thisbrick);
}

void Frame::addRed(Legobrick brick){
    Legobrick thisbrick = brick;
    reds.push_back(thisbrick);
    std::cerr << thisbrick.x << std::endl;
}

Legobrick Frame::returnBlue(){
    if(blues.size()==0){
        return nobrick;
    }
    Legobrick brick = blues.back();
    blues.pop_back();
    return brick;
}

Legobrick Frame::returnRed(){
    if(reds.size() == 0){
        return nobrick;
    }
    Legobrick brick =  reds.back();
    std::cerr << "jeg vil vædde: " << brick.x << std::endl;
    reds.pop_back();
    return brick;
}

Legobrick Frame::returnYellow(){
    if(yellows.size()== 0){
        return nobrick;
    }
    Legobrick brick = yellows.back();
    yellows.pop_back();
    return brick;
}

int Frame:: getPosition(){
    return position;
}

std::string Frame::toString(){
    std::stringstream string;
    string << "blue: " << blues.size() << ", red: " << reds.size() << ", yellow: " << yellows.size();
    return string.str();
}

