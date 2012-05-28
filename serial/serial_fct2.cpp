#include <SerialStream.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include "serial_fct2.h"

using namespace LibSerial;
SerialStream serial_port_PLC ;

void Serial_Open_Port_PLC(string comPort)
{
        serial_port_PLC.Open( comPort ) ;
        if(! serial_port_PLC.good())
	{
		std::cerr<<"Error: could not open serial port"<<std::endl;
		exit(1);
	}
        serial_port_PLC.SetBaudRate( SerialStreamBuf::BAUD_19200) ;
        serial_port_PLC.SetCharSize( SerialStreamBuf::CHAR_SIZE_8 ) ;
        serial_port_PLC.SetNumOfStopBits(1) ;
        serial_port_PLC.SetParity( SerialStreamBuf::PARITY_EVEN ) ;
        serial_port_PLC.SetFlowControl( SerialStreamBuf::FLOW_CONTROL_NONE ) ;
}


void Serial_Send_Message_PLC(int type, int x)
{
	char output_buffer[5];
	int i, coef = 1;
	if(type == 2)
	{
		output_buffer[0]=2;
		for(i=1;i<5;i++)
		{
			output_buffer[i]=0;
		}
	}
	if(type == 3)
	{
		output_buffer[0]=3;
		x*=coef;
		output_buffer[1]=(x & 0xFF000000)>>24;
		output_buffer[2]=(x & 0x00FF0000)>>16;
		output_buffer[3]=(x & 0x0000FF00)>>8;
		output_buffer[4]=x;
	}
    serial_port_PLC.write(output_buffer,5);
}
void Serial_Close_Port_PLC(void)
{
        if(serial_port_PLC.IsOpen())
	{
                serial_port_PLC.Close();
	}
}
