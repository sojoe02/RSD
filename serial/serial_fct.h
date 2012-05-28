/*
 * serial_functions.h
 *
 *  Created on: Mar 3, 2012
 *      Author: dan
 */

#ifndef SERIAL_FCT_H_
#define SERIAL_FCT_H_

#include <SerialStream.h>
#include <string>
using namespace LibSerial ;
using namespace std;

extern SerialStream serial_port ;

void Serial_Open_Port(string comPort);
void Serial_Send_Message(string message);
void Serial_Close_Port(void);

#endif /* SERIAL_FCT_H_ */
