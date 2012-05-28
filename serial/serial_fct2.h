/*
 * serial_functions.h
 *
 *  Created on: Mar 3, 2012
 *      Author: dan
 */

#ifndef SERIAL_FCT2_H_
#define SERIAL_FCT2_H_

#include <SerialStream.h>
#include <string>
using namespace LibSerial ;
using namespace std;

extern SerialStream serial_port_PLC ;

void Serial_Open_Port_PLC(string comPort);
void Serial_Send_Message_PLC(int type, int val_to_send);
void Serial_Close_Port_PLC(void);

#endif /* SERIAL_FCT2_H_ */
