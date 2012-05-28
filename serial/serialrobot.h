#ifndef SERIALROBOT_H
#define SERIALROBOT_H

#include <string>
#include <QtCore>

class SerialRobot
{
public:
    SerialRobot();
    void sendRobotCoor(std::string);
    void sendPLCcmd(int value, int type);
};

#endif // SERIALROBOT_H
