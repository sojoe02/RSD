#include "serialcomm.h"
#include "qextserialport.h"
#include "QtGui"

SerialComm::SerialComm(QWidget *parent) :
    QWidget(parent)
{
    port = new QextSerialPort("COM1");


}

int SerialComm::sendString(QString string){

    port->open(QIODevice::ReadWrite);

    if(port->isOpen()){
        port->setBaudRate(BAUD9600);
        port->setParity(PAR_EVEN);
        port->setFlowControl(FLOW_OFF);
        port->setDataBits(DATA_8);
        port->setStopBits(STOP_1);
    } else return(-1);

    QByteArray ba = string.toLatin1();
    const char *message = ba.data();

    port->write(message);

    return 1;

}
