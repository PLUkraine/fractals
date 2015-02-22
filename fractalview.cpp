#include "fractalview.h"
#include <QResizeEvent>
#include <QtConcurrent>
#include <QDebug>

// this is threadFunc
void wrapperFunc(FractalBuilder* build, std::shared_ptr<Channel<QLineF>> channel, uint level, QRectF square)
{
    build->getFractal(*channel, level, square);
}

FractalView::FractalView(FractalBuilder *build, QWidget *parent, uint defLevel)
    : QWidget(parent),
      builder(build),
      _level(defLevel),
      _image(size()),
      lineTimer(new QTimer(this)),
      _timerDelay(0),
      _linePen(),
      _backgrColor(255,255,255)
{
    connect(lineTimer, SIGNAL(timeout()), this, SLOT(on_lineTimer_timeout()));
    resetElements(size());
}

uint FractalView::level()
{
    return _level;
}

void FractalView::setLevel(uint l)
{
    stopPainting();
    _level = l;
}

const FractalBuilder *FractalView::fractalBuilder()
{
    return builder;
}

void FractalView::setFractalBuilder(FractalBuilder *build)
{
    stopPainting();
    builder = build;
    resetElements(size());
}

QColor FractalView::backgroundColor()
{
    return _backgrColor;
}

void FractalView::setBackgroundColor(QColor color)
{
    pausePainting();
    _backgrColor = color;
    update();
}

QPen FractalView::linePen()
{
    return _linePen;
}

void FractalView::setLinePen(QPen pen)
{
    pausePainting();
    _linePen = pen;
}

int FractalView::timerDelay()
{
    return _timerDelay;
}

void FractalView::setTimerDelay(int milis)
{
    pausePainting();
    if (milis < 0) milis=0;
    _timerDelay = milis;
}

FractalView::~FractalView()
{
    if (builder) delete builder;
}

void FractalView::startPainting()
{
    resetElements(size());
    QRectF r(this->rect().x(), this->rect().y(), this->rect().width(), this->rect().height());
    lineList = std::make_shared<Channel<QLineF>>();
    // we calculate lines in separate thread
    // txn to ejmahler for his channel and SearchVisualizer :)
    QtConcurrent::run(
                wrapperFunc,
                builder,
                lineList,
                _level,
                r
                );
    lineTimer->start(_timerDelay);
}

void FractalView::stopPainting()
{
    if (lineTimer->isActive())
    {
        lineList->closeFront();
        lineList = NULL;
        lineTimer->stop();
        resetElements(size());
    }
}

void FractalView::pausePainting()
{
    if (lineTimer->isActive())
    {
        lineTimer->stop();
    }
    else
    {
        if (lineList.get())
            lineTimer->start(_timerDelay);
    }
}

void FractalView::on_lineTimer_timeout()
{
    if (lineList.get())
    {
        QLineF line;
        if (lineList->pop(line))
        {
            _image.paintOnImage(line, _linePen);
        }
        else
        {
            lineTimer->stop();
            lineList = NULL;
        }
        update();
    }
}

void FractalView::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.fillRect(rect(), _backgrColor);
    _image.paintImage(painter);
}

void FractalView::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event)
    stopPainting();
}

void FractalView::resetElements(const QSize& s)
{
    _image.resetImage(s);
}

