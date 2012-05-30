#include "serialrobot.h"
#include <QtCore>
#include <string>
#include <SerialStream.h>
#include "serial_fct.h"
#include "serial_fct2.h"

using namespace std;

SerialRobot::SerialRobot()
{
}

void SerialRobot::sendRobotCoor(string message){

    string comPort="/dev/ttyS0";
    string message2="300,550,117,2";


    string initial_configuration =" insert init coord";
    char c;
    bool exit_program=false;
    bool data_to_send=false;

    // open and send initial position to the robot
    Serial_Open_Port(comPort);

    Serial_Send_Message(message);

    Serial_Close_Port();
}



/******************************
 * type = 2 => return to home
 * type = 3 => go to position indicated by val_to_send
 * the position is the absolute value
 *
 * ToDo:
 *
 * need to modify the coef value in Send function to make
 * the conversion between the value received from the camera and
 * the value required by the plc (0 -> 200000)
 * need to determine the com port used by the USB to Serial adapter( check if it's ttyUSB0)
 */

void SerialRobot::sendPLCcmd(int value, int type){

    string comPort="/dev/ttyUSB0";
        int val_to_send;

        //val_to_send = value;//4;
        //type2 = type;//2

        Serial_Open_Port_PLC(comPort);
        Serial_Send_Message_PLC(type, value);
        Serial_Close_Port_PLC();
    //return EXIT_SUCCESS ;
}
