#ifndef HEIGHWAYDRAGON_H
#define HEIGHWAYDRAGON_H
#include "fractalbuilder.h"

class HeighwayDragon : public FractalBuilder
{
public:
    void getFractal(Channel<QLineF> &channel, uint level, QRectF square);
    ~HeighwayDragon();
private:
    void recursion(Channel<QLineF> &lines, QLineF& base, uint level);
};

#endif // HEIGHWAYDRAGON_H
