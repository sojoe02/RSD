#ifndef ORDERLOGIC_H
#define ORDERLOGIC_H

#include <QWidget>
#include <QVector>
#include <vector>
#include <frame.h>
#include <map>
#include <vision/VisionSystem.h>
#include <serial/serialrobot.h>
#include "Globals.h"

class orderlogic : public QWidget
{
    Q_OBJECT
public:
    explicit orderlogic(QWidget *parent = 0);
    
signals:
    void orderdone();
    
public slots:
    void scanTable();
    void resetSystem();
    void makeFrame(int j);
    void handleOrder(std::vector<int> orderarray);
    void timedSC();

private:



    void mapFromVisionToRobot(int Vframe, Legobrick);


    //the different robotframes:

    std::vector<Frame*> frames;

    int activeframe_ptr;
    SerialRobot serial;
    //gandry position:
    static const int gantryMax = 200000;
    static const int no_frames = 2;
    static const int FInterval = 38400;
    //x value for binning in different frames:
    static const int Xmax = 530;
    static const int Xmin = 54;
    //difference between vision and robot system:
    static const int Yoff = 323;
    static const int Xoff = -86;    
    //gandry delay for movement purposes:
    static const int ScanDelay = 14000;
static const int PickupDelay = 10000;
    static const int Roff = 130*2;
    static const int PickupOff = 52224+17780;
    static const int PostScanOff = 13824;


};

#endif // ORDERLOGIC_H
