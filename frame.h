#ifndef FRAME_H
#define FRAME_H

#include <vision/VisionSystem.h>

#include <QVector>
#include <string>
#include <vector>
#include <Globals.h>

class Frame
{
public:    

    Frame(int position);

    void addBlue(Legobrick);
    void addRed(Legobrick);
    void addYellow(Legobrick);

    Legobrick returnBlue();
    Legobrick returnRed();
    Legobrick returnYellow();

    int getPosition();

    std::string toString();

private:

    std::vector<Legobrick> blues;
    std::vector<Legobrick> reds;
    std::vector<Legobrick> yellows;

    int position;

    Legobrick nobrick;
};

#endif // FRAME_H
