#ifndef FRAME_H
#define FRAME_H

#include <vision/VisionSystem.h>

#include <QVector>

class Frame
{
public:
    Frame(int postion);

    void addBlue(VisionSystem::Legobrick brick);
    void addRed(VisionSystem::Legobrick brick);
    void addYellow(VisionSystem::Legobrick brick);

    VisionSystem::Legobrick returnBlue();
    VisionSystem::Legobrick returnRed();
    VisionSystem::Legobrick returnYellow();

    int getPosition();

private:

    std::vector<VisionSystem::Legobrick> blues;
    std::vector<VisionSystem::Legobrick> reds;
    std::vector<VisionSystem::Legobrick> yellows;

    int position;

    struct VisionSystem::Legobrick nobrick;
};

#endif // FRAME_H
