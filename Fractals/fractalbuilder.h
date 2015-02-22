#ifndef FRACTALBUILDER_H
#define FRACTALBUILDER_H
#include <QVector>
#include <QRectF>
#include <QLineF>
#include "Util/channel.h"

/**
 * @brief The FractalBuilder class - strategy pattern, calculates lines which we will paint
 */
class FractalBuilder
{
public:
    virtual void getFractal(Channel<QLineF>& channel, uint level, QRectF square)=0;
    virtual ~FractalBuilder() {}
};

#endif // FRACTALBUILDER_H
