#ifndef PACKMLW_H
#define PACKMLW_H

#include <QState>
#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include "restwidget.h"

class PackMLw : public QWidget
{
    Q_OBJECT
public:
    explicit PackMLw(QWidget *parent = 0, RestWidget *rest=0);
    
signals:
    void sc();
    void orderDone();

    
public slots:
 void stateAborting();
 void stateAborted();
 void stateClear();
 void stateClearing();
 void stateStopping();
 void stateStopped();
 void stateReady();
 void stateSuspending();
 void stateSuspended();
 void stateUnsuspending();
 void stateResetting();
 void stateIdle();
 void stateStarting();
 void stateExecute();
 void stateCompleting();
 void stateComplete();
 void stateHolding();
 void stateHeld();
 void stateUnholding();

 void handlingOrder();

 void timedSC();

private:

    //STATES:
    //first define the statemachince:
    QStateMachine *machine;
    //states of the packml statemachine:
    QState *aborting;
    QState *aborted;
    QState *clear;
    //states of the clear state:
    QState *clearing;
    QState *stopping;
    QState *stopped;
    QState *ready;
    //states of the ready state:
    QState *suspending;
    QState *suspended;
    QState *unsuspending;
    QState *resetting;
    QState *idle;
    QState *starting;
    QState *execute;
    QState *completing;
    QState *complete;
    QState *holding;
    QState *held;
    QState *unholding;
    //methods:
    void definemachine();
    void properties();

    //widgets:
    QPushButton *holdButton;
    QPushButton *suspendButton;
    QPushButton *unholdButton;
    QPushButton *unsuspendButton;
    QPushButton *resetButton;
    QPushButton *stopButton;
    QPushButton *abortButton;
    QPushButton *startButton;
    QPushButton *clearButton;


    QLabel *label;
    QLabel *statusLabel;
    QLabel *imageLabel;

    RestWidget *restwidget;

    int delay;
};

#endif // PACKMLW_H
