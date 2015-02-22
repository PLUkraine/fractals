#include "heighwaydragon.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include <QVector2D>
const float sin45 = sin(M_PI/4);
const float cos45 = cos(M_PI/4);
const float sin135 = sin(3*M_PI/4);
const float cos135 = cos(3*M_PI/4);
const float oneoversqr = 1/sqrt(2);

QVector2D rotate45(const QVector2D& vect)
{
    float x = vect.x()*cos45 - vect.y()*sin45;
    float y = vect.x()*sin45 + vect.y()*cos45;
    return QVector2D(x, y);
}

QVector2D rotate135(const QVector2D& vect)
{
    float x = vect.x()*cos135 - vect.y()*sin135;
    float y = vect.x()*sin135 + vect.y()*cos135;
    return QVector2D(x, y);
}

void HeighwayDragon::getFractal(Channel<QLineF>& channel, uint level, QRectF square)
{
    // trim square
    int wq = 1.5 * square.height();
    int hq = 2 * square.width() / 3;
    int h = (wq < square.width() ? wq / 3 : hq / 2);
    QRectF rect;
    float shift = h/3;
    rect.setSize(square.size().scaled(3*h, 2*h, Qt::IgnoreAspectRatio));

    // all shifts were taken from wikipedia
    QPointF A;
    A.setX(rect.left() + h/3);
    A.setY(rect.top() + h + shift);
    QPointF B;
    B.setX(rect.left() + rect.width()/2 - h/6);
    B.setY(rect.top() + shift);
    QPoint C;
    C.setX(rect.right() - h/2 - h/6);
    C.setY(rect.top() + h + shift);
    /*
     * n---B
     * |   |
     * A   n---C
     *
     */
    QLineF AB(A, B);
    QLineF CB(C, B);

    recursion(channel, AB, level);
    recursion(channel, CB, level);
    channel.closeBack();
}

HeighwayDragon::~HeighwayDragon()
{
    // lol
}

void HeighwayDragon::recursion(Channel<QLineF> &lines, QLineF &base, uint level)
{
    if (!(level-->0))
    {
        lines.push(base);
        return;
    }
    QPointF A = base.p1();
    QPointF C = base.p2();
    QVector2D AC(C-A);
    QVector2D ABv = rotate45(AC)*oneoversqr;
    QPointF B = A + ABv.toPointF();

    QLineF AB(A, B);
    QLineF CB(C, B);
    recursion(lines, AB, level);
    recursion(lines, CB, level);
}

