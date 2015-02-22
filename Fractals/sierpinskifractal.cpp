#include "sierpinskifractal.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include <QVector2D>
const float sin60 = sin(M_PI/3);
const float sqrt3 = 1.73205;

void SierpinskiFractal::getFractal(Channel<QLineF> &channel, uint level, QRectF square)
{
    // transform square to appropriate rectangle
    float h = square.width()*sin60;
    float w = square.height()/sin60;
    float a = (h < square.height() ? square.width() : w);
    QRectF rect;
    rect.setSize(square.size().scaled(a, a*sin60, Qt::IgnoreAspectRatio));
    // now we have nice rectangle that has width of a and height of a*sqrt(3)/2

    // add three main lines
    channel.push(QLineF(rect.bottomLeft().x(),
                       rect.bottomLeft().y(),
                       rect.topRight().x()/2,
                       rect.topRight().y())
                 );
    channel.push(QLineF(rect.bottomRight().x(),
                       rect.bottomRight().y(),
                       rect.topRight().x()/2,
                       rect.topRight().y())
                );
    channel.push(QLineF(rect.bottomLeft().x(),
                       rect.bottomLeft().y(),
                       rect.bottomRight().x(),
                       rect.bottomRight().y())
                );

    // calculate all other lines
    recursion(channel, level, rect);
    channel.closeBack();
}

SierpinskiFractal::~SierpinskiFractal()
{
    // lol
}

void SierpinskiFractal::recursion(Channel<QLineF> &lines, uint level, const QRectF &rect)
{
    /*       C
     *
     *     Aq  Bq
     *
     *   A   Cq   B
     */
    if (!(level-->0)) return;
    QPointF A (rect.bottomLeft());
    QPointF B (rect.bottomRight());
    QVector2D AB(B-A);

    QPointF Cq = A + AB.toPointF()/2;
    QPointF C(Cq.x(),
              rect.top());

    QVector2D AC(C-A);
    QPointF Aq = A + AC.toPointF()/2;

    QVector2D BC(C-B);
    QPointF Bq = B + BC.toPointF()/2;

    // we need to paint segments AqBq, AqCq, BqCq
    lines.push(QLineF(Aq,Bq));
    lines.push(QLineF(Cq,Bq));
    lines.push(QLineF(Aq,Cq));

    // now we calculate new rectangles for the new recursion step
    float w = fabs(Cq.x() - A.x());
    float h = fabs(Aq.y() - Cq.y());
    QRectF rect1(A.x(), Aq.y(), w, h);
    QRectF rect2(Cq.x(), Bq.y(), w, h);
    QRectF rect3(Aq.x(), C.y(), w, h);
    recursion(lines, level, rect1);
    recursion(lines, level, rect2);
    recursion(lines, level, rect3);
}
