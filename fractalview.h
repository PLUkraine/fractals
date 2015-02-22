#ifndef FRACTALVIEW_H
#define FRACTALVIEW_H

#include <QWidget>
#include <QPainter>
#include <QRectF>
#include <QRect>
#include <QImage>
#include <memory>
#include "Fractals/fractalbuilder.h"
#include "Util/imageproxy.h"

/**
 * @brief The FractalView class is widget that visualizes the fractal
 */
class FractalView : public QWidget
{
    Q_OBJECT
public:
    explicit FractalView(FractalBuilder * build, QWidget *parent = 0, uint defLevel=0);
    uint level();
    void setLevel(uint l);
    const FractalBuilder* fractalBuilder();
    void setFractalBuilder(FractalBuilder* build);
    QColor backgroundColor();
    void setBackgroundColor(QColor color);
    QPen linePen();
    void setLinePen(QPen pen);
    int timerDelay();
    void setTimerDelay(int milis);

    ~FractalView();

public slots:
    void startPainting();
    void stopPainting();
    void pausePainting();
    void on_lineTimer_timeout();

protected:
    void paintEvent(QPaintEvent*e);

    void resetElements(const QSize &s);

    void resizeEvent(QResizeEvent *event);
private:
    FractalBuilder* builder;
    std::shared_ptr<Channel<QLineF>> lineList;
    uint _level;
    ImageProxy _image;
    QTimer *lineTimer;
    int _timerDelay;
    QPen _linePen;
    QColor _backgrColor;
};

#endif // FRACTALVIEW_H
