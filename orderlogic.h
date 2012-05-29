#ifndef ORDERLOGIC_H
#define ORDERLOGIC_H

#include <QWidget>
#include <QVector>
#include <frame.h>
#include <vision/VisionSystem.h>

class orderlogic : public QWidget
{
    Q_OBJECT
public:
    explicit orderlogic(QWidget *parent = 0);
    
signals:
    
public slots:
    void scanTable();
    void timedSC();

private:

    void mapFromVisionToRobot(int Vframe, VisionSystem::Legobrick);

    void brickBinning(std::vector<VisionSystem::Legobrick> bricks, Frame *RF1, Frame *RF2);

    //the different robotframes:
    Frame *RF_11;
    Frame *RF_12;

    Frame *RF_21;
    Frame *RF_22;

    Frame *RF_31;
    Frame *RF_32;

    Frame *RF_41;
    Frame *RF_42;

    //gandry position:
    static const int gantryMax = 200000;
    static const int VFinterval = gantryMax/4;
    //x value for binning in different frames:
    static const int Xmax = 530;
    static const int Xbin = Xmax/2;
    //difference between vision and robot system:
    static const int Yoff = 318;
    static const int Xoff = -86;
    //gandry position of the vision frames:
    static const int VF_1pos = 0;
    static const int VF_2pos = 1*VFinterval-Xoff;
    static const int VF_3pos = 2*VFinterval-Xoff;
    static const int VF_4pos = 3*VFinterval-Xoff;
    //gandry delay for movement purposes:
    static const int DELAY = 10000;



};

#endif // ORDERLOGIC_H
