#ifndef BRICKHANDLER_H
#define BRICKHANDLER_H

#include <QWidget>
#include <QtGui>

class BrickHandler : public QWidget
{
    Q_OBJECT
public:
    explicit BrickHandler(QWidget *parent = 0);
    
signals:
    
public slots:

    void processOrder(QVector<int> currentOrder);
    void scanTable();
    void moveGantry();

private:


    
};

#endif // BRICKHANDLER_H
