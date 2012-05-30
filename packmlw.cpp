#include "packmlw.h"
#include "iostream"
#include "restwidget.h"
#include "oeewidget.h"
#include "orderlogic.h"
#include <QtGui>



PackMLw::PackMLw(QWidget *parent, RestWidget *rest, OEEWidget *oee, QListWidget *output) :
    QWidget(parent), restwidget(rest), oeewidget(oee), output(output)
{
    this->setWindowTitle(QApplication::translate("PackML", "Pack ML"));

    //DEFINE THE SUBWIDGETS (buttons, labels etc.):
    holdButton = new QPushButton(QApplication::translate("PackML", "Hold"));
    suspendButton = new QPushButton(QApplication::translate("PackML", "Suspend"));
    unholdButton = new QPushButton(QApplication::translate("PackML", "Un-Hold"));
    unsuspendButton = new QPushButton(QApplication::translate("PackML", "Un-Suspend"));
    resetButton = new QPushButton(QApplication::translate("PackML","Reset"));
    stopButton = new QPushButton(QApplication::translate("PackML","Stop"));
    abortButton = new QPushButton(QApplication::translate("PackML", "Abort"));
    startButton = new QPushButton(QApplication::translate("PackML","Start"));
    clearButton = new QPushButton(QApplication::translate("PackML","Clear"));

    statusLabel = new QLabel(QApplication::translate("PackML", "....."));

    //DEFINE THE GRAPHICS WIDGET:
    imageLabel = new QLabel;
    //imageLabel->setBackgroundRole(QPalette::Base);
    //imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->setPixmap(QPixmap(QPixmap(":/packmlressource/init.png")));

    QPalette palette = this->palette();
    palette.setColor( backgroundRole(), QColor( 255, 255, 255) );


    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setPalette(palette);
    scrollArea->setAutoFillBackground(true);
    //scrollArea->setMaximumHeight(200);
    scrollArea->setFrameShape(QFrame::NoFrame);
    //scrollArea->setMaximumWidth(400);
    scrollArea->setWidget(imageLabel);

    this->setPalette( palette );
    this->setAutoFillBackground( true );




    //SET THE LAYOUT:
    //make a image widget with layout:
    QVBoxLayout *imagelayout = new QVBoxLayout();
    imagelayout->addWidget(scrollArea);
    QWidget *imagewidget = new QWidget();
    //imagewidget->setFixedSize(300,600);
    imagewidget->setLayout(imagelayout);

    QHBoxLayout *buttonlayout = new QHBoxLayout();

    buttonlayout->addWidget(startButton);
    buttonlayout->addWidget(resetButton);
    buttonlayout->addWidget(clearButton);
    buttonlayout->addWidget(holdButton);
    buttonlayout->addWidget(suspendButton);
    buttonlayout->addWidget(unholdButton);
    buttonlayout->addWidget(unsuspendButton);



    abortButton->setFixedHeight(50);
    stopButton->setFixedHeight(50);

    QGridLayout *gridlayout = new QGridLayout();

    gridlayout->addWidget(abortButton,1,1);
    gridlayout->addWidget(stopButton,2,1);
    gridlayout->addWidget(oeewidget,3,1);

    QWidget *gridbuttonwidget = new QWidget();
    output = new QListWidget();

    gridbuttonwidget->setLayout(gridlayout);



    holdButton->hide();
    suspendButton->hide();
    unsuspendButton->hide();
    unholdButton->hide();
    resetButton->hide();
    stopButton->hide();
    startButton->hide();
    clearButton->hide();

    QWidget *buttonwidget = new QWidget();
    //buttonwidget->setFixedWidth(200);
    buttonwidget->setLayout(buttonlayout);


    //make the packML widget layout and add all items:
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(buttonwidget,2,1);
    layout->addWidget(gridbuttonwidget,3,1);
    layout->addWidget(imagewidget,1,1);

    setLayout(layout);

    definemachine();

    delay=1500;

    //initialize the orderLogic and hook it up:
    orderlog = new orderlogic();
    //hook up the signals to the statemachine:



    //Order flow:
    QObject::connect(starting, SIGNAL(entered()), restwidget, SLOT(getOrderUrls()));


    QObject::connect(this,SIGNAL(neworder()),restwidget,SLOT(getNewOrder()));
    QObject::connect(restwidget,SIGNAL(sendOrder(QVector<int>*)),orderlog,SLOT(handleOrder(std::vector<int>)));
    QObject::connect(orderlog,SIGNAL(orderdone()),restwidget,SLOT(orderDone()));
    QObject::connect(orderlog,SIGNAL(orderdone()),this,SLOT(timedSC()));
    //QObject::connect(orderlog,SIGNAL(orderincomplete()),reswidget,SLOT())
    //QObject::connect(this,)

    //hook up the signals:





}

void PackMLw::definemachine(){
    //DEFINE THE STATE MACHINE:
    //define the states:
    machine = new QStateMachine(this);
    aborting = new QState();            aborted = new QState();
    clear = new QState();

    clearing = new QState(clear);       stopping = new QState(clear);
    stopped = new QState(clear);        ready = new QState(clear);

    suspending = new QState(ready);     suspended = new QState(ready);
    unsuspending = new QState(ready);   resetting = new QState(ready);
    idle = new QState(ready);           starting = new QState(ready);
    execute= new QState(ready);        completing = new QState(ready);
    complete = new QState(ready);       holding = new QState(ready);
    held = new QState(ready);           unholding = new QState(ready);

    //add the transitions:
    aborting->addTransition(this, SIGNAL(sc()),aborted);
    aborted->addTransition(clearButton,SIGNAL(pressed()),clearing);
    clearing->addTransition(this,SIGNAL(sc()),stopped);
    stopping->addTransition(this,SIGNAL(sc()),stopped);
    stopped->addTransition(resetButton,SIGNAL(pressed()),resetting);

    suspending->addTransition(this,SIGNAL(sc()),suspended);
    suspended->addTransition(unsuspendButton,SIGNAL(pressed()),unsuspending);
    unsuspending->addTransition(this,SIGNAL(sc()),execute);
    resetting->addTransition(this,SIGNAL(sc()),idle);
    idle->addTransition(startButton,SIGNAL(pressed()),starting);
    starting->addTransition(this,SIGNAL(sc()),execute);
    execute->addTransition(this,SIGNAL(sc()),completing);
    execute->addTransition(holdButton,SIGNAL(pressed()),holding);
    execute->addTransition(suspendButton,SIGNAL(pressed()),suspending);
    completing->addTransition(this,SIGNAL(sc()),complete);
    complete->addTransition(resetButton,SIGNAL(pressed()),resetting);
    holding->addTransition(this,SIGNAL(sc()),held);
    held->addTransition(unholdButton,SIGNAL(pressed()),unholding);
    unholding->addTransition(this,SIGNAL(sc()),execute);

    clear->addTransition(abortButton,SIGNAL(pressed()),aborting);
    ready->addTransition(stopButton,SIGNAL(pressed()),stopping);

    //set up the slots (connecting to them):
    QObject::connect(aborting, SIGNAL(entered()), this, SLOT(stateAborting()));
    QObject::connect(aborted, SIGNAL(entered()), this, SLOT(stateAborted()));
    QObject::connect(clear, SIGNAL(entered()), this, SLOT(stateClear()));
    QObject::connect(clearing, SIGNAL(entered()), this, SLOT(stateClearing()));
    QObject::connect(stopping, SIGNAL(entered()), this, SLOT(stateStopping()));
    QObject::connect(stopped, SIGNAL(entered()), this, SLOT(stateStopped()));
    QObject::connect(ready, SIGNAL(entered()), this, SLOT(stateReady()));
    QObject::connect(suspending, SIGNAL(entered()), this, SLOT(stateSuspending()));
    QObject::connect(suspended, SIGNAL(entered()), this, SLOT(stateSuspended()));
    QObject::connect(unsuspending, SIGNAL(entered()), this, SLOT(stateUnsuspending()));
    QObject::connect(resetting, SIGNAL(entered()), this, SLOT(stateResetting()));
    QObject::connect(idle, SIGNAL(entered()), this, SLOT(stateIdle()));
    QObject::connect(starting, SIGNAL(entered()), this, SLOT(stateStarting()));
    QObject::connect(execute, SIGNAL(entered()), this, SLOT(stateExecute()));
    QObject::connect(completing, SIGNAL(entered()), this, SLOT(stateCompleting()));
    QObject::connect(complete, SIGNAL(entered()), this, SLOT(stateComplete()));
    QObject::connect(holding, SIGNAL(entered()), this, SLOT(stateHolding()));
    QObject::connect(held, SIGNAL(entered()), this, SLOT(stateHeld()));
    QObject::connect(unholding, SIGNAL(entered()), this, SLOT(stateUnholding()));

    //set up buttons(when they appear):
    QObject::connect(ready, SIGNAL(entered()), stopButton, SLOT(show()));
    QObject::connect(ready, SIGNAL(exited()), stopButton, SLOT(hide()));

    QObject::connect(clear, SIGNAL(entered()), abortButton, SLOT(show()));
    QObject::connect(clear, SIGNAL(exited()), abortButton, SLOT(hide()));

    QObject::connect(idle, SIGNAL(entered()), startButton, SLOT(show()));
    QObject::connect(idle, SIGNAL(exited()), startButton, SLOT(hide()));

    QObject::connect(execute, SIGNAL(entered()), holdButton, SLOT(show()));
    QObject::connect(execute, SIGNAL(exited()), holdButton, SLOT(hide()));
    QObject::connect(execute, SIGNAL(entered()), suspendButton, SLOT(show()));
    QObject::connect(execute, SIGNAL(exited()), suspendButton, SLOT(hide()));

    QObject::connect(held, SIGNAL(entered()), unholdButton, SLOT(show()));
    QObject::connect(held, SIGNAL(exited()), unholdButton, SLOT(hide()));

    QObject::connect(suspended, SIGNAL(entered()), unsuspendButton, SLOT(show()));
    QObject::connect(suspended, SIGNAL(exited()), unsuspendButton, SLOT(hide()));

    QObject::connect(complete, SIGNAL(entered()), resetButton, SLOT(show()));
    QObject::connect(complete, SIGNAL(exited()), resetButton, SLOT(hide()));

    QObject::connect(aborted, SIGNAL(entered()), clearButton, SLOT(show()));
    QObject::connect(aborted, SIGNAL(exited()), clearButton, SLOT(hide()));

    QObject::connect(stopped, SIGNAL(entered()), resetButton, SLOT(show()));
    QObject::connect(stopped, SIGNAL(exited()), resetButton, SLOT(hide()));


    //add the states to the machine:
    machine->addState(aborting);
    machine->addState(aborted);
    machine->addState(clear);

    clear->setInitialState(clearing);
    ready->setInitialState(resetting);

    machine->setInitialState(clear);
    machine->start();
}

//THE SIGNAL FUNCTIONS:
void PackMLw::timedSC(){    
    emit sc();
}

//THE SLOT FUNCTIONS:
void PackMLw::stateAborting(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/aborting.png"));
    QTimer::singleShot(1500,this,SLOT(timedSC()));
}

void PackMLw::stateAborted(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/aborted.png"));
}

void PackMLw::stateClear(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/clear.png"));

}

void PackMLw::stateClearing(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/clearing.png"));
    QTimer::singleShot(1500,this,SLOT(timedSC()));
}

void PackMLw::stateStopping(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/stopping.png"));
    QTimer::singleShot(delay,this,SLOT(timedSC()));
}

void PackMLw::stateStopped(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/stopped.png"));
}

void PackMLw::stateReady(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/ready.png"));

}

void PackMLw::stateSuspending(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/suspending.png"));
    QTimer::singleShot(delay,this,SLOT(timedSC()));
}

void PackMLw::stateSuspended(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/suspended.png"));
}

void PackMLw::stateUnsuspending(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/unsuspending.png"));
    QTimer::singleShot(delay,this,SLOT(timedSC()));
}

void PackMLw::stateResetting(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/resetting.png"));
    QTimer::singleShot(delay,this,SLOT(timedSC()));
}

void PackMLw::stateIdle(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/idle.png"));
}

void PackMLw::stateStarting(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/starting.png"));
    QTimer::singleShot(delay,this,SLOT(timedSC()));
}

void PackMLw::stateExecute(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/execute.png"));
    //QTimer::singleShot(10000,this,SLOT(timedSC()));
    //when done (needs to be implemented):
    //emit sc();
    emit neworder();
}

void PackMLw::stateCompleting(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/completing.png"));
    QTimer::singleShot(delay,this,SLOT(timedSC()));
}

void PackMLw::stateComplete(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/complete.png"));
}

void PackMLw::stateHolding(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/holding.png"));
    QTimer::singleShot(delay,this,SLOT(timedSC()));
}

void PackMLw::stateHeld(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/held.png"));
}

void PackMLw::stateUnholding(){
    imageLabel->setPixmap(QPixmap(":/packmlressource/unholding.png"));
    QTimer::singleShot(delay,this,SLOT(timedSC()));
}

void PackMLw::handlingOrder(){
    //this will handle all the order logic, and emit a signal whenever it's done handling an order.
    //TODO!
}











