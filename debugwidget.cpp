#include "debugwidget.h"
//#include "serial/serialcomm.h"
//#include "plccomms/rsd_server.h"
#include "vision/VisionSystem.h"
#include "serial/serialrobot.h"
#include "string"
#include <QtCore>
#include <iostream>
#include <orderlogic.h>

DebugWidget::DebugWidget(QWidget *parent) :
    QWidget(parent)
{

    //setup up the buttons and such:
    runPLCtest = new QPushButton("Run PLC test", this);
    runRobotest = new QPushButton("Run Robot test", this);
    runVisiontest = new QPushButton("Run Vision test", this);
    runOrderSystemtest = new QPushButton("Run Order System Test", this);

    //connect the buttons to the appropriate slots:
    connect(runPLCtest, SIGNAL(pressed()), this,SLOT(testPLC()));
    connect(runRobotest,SIGNAL(pressed()), this, SLOT(testRobot()));
    connect(runVisiontest,SIGNAL(pressed()), this, SLOT(testVision()));
    connect(runOrderSystemtest,SIGNAL(pressed()),this,SLOT(testOrderSystem()));
    //make the listwidget, for debugging feedback:
    feedback = new QListWidget;
    //setup the layout of the widget:
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(runPLCtest,0,0);
    layout->addWidget(runRobotest,0,1);
    layout->addWidget(runVisiontest,0,2);
    layout->addWidget(runOrderSystemtest,0,3);
    layout->addWidget(feedback,1,0,4,4);

    setLayout(layout);
}

void DebugWidget:: testPLC()
{
    bool ok;
    int position = QInputDialog::getInt(this,tr("input position"),tr("placeholder"),100,0,199999,1,&ok);

    SerialRobot serialrobot;

    serialrobot.sendPLCcmd(position,3);
}

void DebugWidget:: testRobot()
{
    //    SerialComm *serial = new SerialComm();
        feedback->addItem("Performing serial to robot test");
        feedback->addItem("Waiting for parameters");
//
     bool ok;
//100,400,90,1
    QString text = QInputDialog::getText(this,tr("input coordinates"),tr("placeholder"),QLineEdit::Normal,tr("300,550,117,2"), &ok);
    std::string test = std::string(text.toAscii());

    //    if (ok && !text.isEmpty()){
    //        feedback->addItem("Sending:\t" + text);
    //        int status = serial->debugSendString(text);
    //        if(status == -1){
    //            feedback->addItem("Serial port cannot be opened");
    //        }
    //        if(status == 1){
    //            feedback->addItem("Data send to serial port successfully");
    //        }
    //    }
    //    serial->deleteLater();
    SerialRobot serialrobot;
    std::string tmpString= "300,550,117,2";
    serialrobot.sendRobotCoor(test);
}

void DebugWidget:: testVision()
{
    feedback->addItem("Performing vision test");
    feedback->addItem("Printing found brick locations:");
    VisionSystem vs;

    cv::namedWindow("output", CV_WINDOW_NORMAL);

    vs.findBricks();


    for (int i = 0; i < vs.bricks.size(); i++)
    {
        QString color = "undefined";
        if(vs.bricks[i].color == 0){
            color = "Blue";
        } else if(vs.bricks[i].color == 1){
            color = "Red";
        } else if(vs.bricks[i].color == 2){
            color = "Yellow";
        }
        QString thing = color
                + "\t found at: [" + QString::number(vs.bricks[i].x)
                + "," + QString::number(vs.bricks[i].y)
                +"] - : \t" + QString::number(vs.bricks[i].orientation);

        feedback->addItem(thing);        
    }

    feedback->addItem("Vision test done");
    cv::imshow("output", vs.outputImage);
    cv::waitKey(1);
}

void DebugWidget:: testOrderSystem()
{
    //scan the table
    feedback->addItem("Scanning the table");
    orderlogic logic;
    logic.scanTable();
}
