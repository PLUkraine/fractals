#ifndef SIERPINSKIFRACTAL_H
#define SIERPINSKIFRACTAL_H
#include "fractalbuilder.h"

/**
 * @brief The SierpinskiFractal class builds the Sierpinski fractal
 */
class SierpinskiFractal : public FractalBuilder
{
public:
    void getFractal(Channel<QLineF>& channel,uint level, QRectF square);
    ~SierpinskiFractal();
private:
    void recursion(Channel<QLineF>& lines, uint level,const QRectF &rect);
};

#endif // SIERPINSKIFRACTAL_H
