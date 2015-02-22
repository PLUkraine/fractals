#include "imageproxy.h"
#include <QDebug>

ImageProxy::ImageProxy(QSize s) : _image(s, QImage::Format_ARGB32_Premultiplied)
{
}

void ImageProxy::resetImage(const QSize &s)
{
    std::lock_guard<std::mutex> lock(_imageMutex);
    _image = QImage(s, QImage::Format_ARGB32_Premultiplied);
    _image.fill(Qt::transparent);
}

void ImageProxy::paintOnImage(QLineF& line, QPen &pen)
{
    std::lock_guard<std::mutex> lock(_imageMutex);
    QPainter painter;
    painter.begin(&_image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.drawLine(line);
    painter.end();
}

void ImageProxy::paintImage(QPainter& painter)
{
    std::unique_lock<std::mutex> lock(_imageMutex);
    painter.drawImage(0,0,_image);
}

ImageProxy::~ImageProxy()
{

}

