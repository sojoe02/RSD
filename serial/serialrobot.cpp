#include "serialrobot.h"
#include <QtCore>
#include <string>
#include <SerialStream.h>
#include "serial_fct.h"

using namespace std;

SerialRobot::SerialRobot()
{
}

void SerialRobot::send(){

    string comPort="/dev/ttyS0";
    string message="300,550,117,2";
    //string message="9";
    string initial_configuration =" insert init coord";
    char c;
    bool exit_program=false;
    bool data_to_send=false;

    // open and send initial position to the robot
    Serial_Open_Port(comPort);

    //Serial_Send_Message(message);
    Serial_Send_Message(message);
    //Serial_Send_Message("400");
    //Serial_Send_Message("45");
    Serial_Close_Port();

}
