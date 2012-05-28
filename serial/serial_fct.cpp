#include <SerialStream.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include "serial_fct.h"

using namespace LibSerial;
SerialStream serial_port ;

void Serial_Open_Port(string comPort)
{
	serial_port.Open( comPort ) ;
	if(! serial_port.good())
	{
		std::cerr<<"Error: could not open serial port"<<std::endl;
		exit(1);
	}
	serial_port.SetBaudRate( SerialStreamBuf::BAUD_9600) ;
	serial_port.SetCharSize( SerialStreamBuf::CHAR_SIZE_8 ) ;
	serial_port.SetNumOfStopBits(1) ;
	serial_port.SetParity( SerialStreamBuf::PARITY_EVEN ) ;
	serial_port.SetFlowControl( SerialStreamBuf::FLOW_CONTROL_NONE ) ;
}
void Serial_Send_Message(string message)
{
	char output_buffer[64];
    int i,message_length;
    message_length=message.length();
    for(i=0;i<message_length;i++)
    {
    	output_buffer[i]=message[i];
    }
    serial_port.write(output_buffer,message_length);

}
void Serial_Close_Port(void)
{
	if(serial_port.IsOpen())
	{
		serial_port.Close();
	}
}
