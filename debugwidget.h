#ifndef DEBUGWIDGET_H
#define DEBUGWIDGET_H

#include <QWidget>
#include <QtGui>


class DebugWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DebugWidget(QWidget *parent = 0);
    
signals:
    
public slots:

    void testPLC();
    void testRobot();
    void testVision();
    void testOrderSystem();

private:

    QPushButton *runPLCtest;
    QPushButton *runRobotest;
    QPushButton *runVisiontest;
    QPushButton *runOrderSystemtest;

    QListWidget *feedback;
    
};

#endif // DEBUGWIDGET_H
