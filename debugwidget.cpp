#include "debugwidget.h"
#include "serial/serialcomm.h"
#include "plccomms/rsd_server.h"
#include "vision/VisionSystem.h"

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

}

void DebugWidget:: testRobot()
{

}

void DebugWidget:: testVision()
{
    feedback->addItem("Performing vision test");
    feedback->addItem("Printing found brick locations:");
    VisionSystem vs;

    //cv::namedWindow("output", CV_WINDOW_NORMAL);

    vs.findBricks();

    for (int i = 0; i < vs.bricks.size(); i++)
    {
        QString thing = QString::number(vs.bricks[i].color)
                + " found at: [" + QString::number(vs.bricks[i].x)
                + "," + QString::number(vs.bricks[i].y)
                +"] - : " + QString::number(vs.bricks[i].orientation);

        feedback->addItem(thing);
    }

    feedback->addItem("Vision test done");

    //cv::imshow("output", vs.outputImage);
    //cv::waitKey(0);

}

void DebugWidget:: testOrderSystem()
{

}
