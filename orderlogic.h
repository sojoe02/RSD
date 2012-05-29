#ifndef ORDERLOGIC_H
#define ORDERLOGIC_H

#include <QWidget>
#include <QVector>
#include <vector>
#include <frame.h>
#include <map>
#include <vision/VisionSystem.h>

class orderlogic : public QWidget
{
    Q_OBJECT
public:
    explicit orderlogic(QWidget *parent = 0);
    
signals:
    
public slots:
    void scanTable();
    void resetSystem();
    void handleOrder(std::vector<int> orderarray);
    void timedSC();

private:

    void mapFromVisionToRobot(int Vframe, VisionSystem::Legobrick);


    //the different robotframes:

    std::vector<Frame*> frames;

    int activeframe_ptr;
    //gandry position:
    static const int gantryMax = 200000;
    static const int no_frames = 6;
    static const int FInterval = gantryMax/no_frames;
    //x value for binning in different frames:
    static const int Xmax = 530;
    //difference between vision and robot system:
    static const int Yoff = 318;
    static const int Xoff = -86;
    //gandry position of the vision frames:
    static const int VF_1pos = 0;
    static const int VF_2pos = 1*FInterval-Xoff;
    static const int VF_3pos = 2*FInterval-Xoff;
    static const int VF_4pos = 3*FInterval-Xoff;
    //gandry delay for movement purposes:
    static const int DELAY = 10000;
    static const int Roff = 100;


};

#endif // ORDERLOGIC_H
