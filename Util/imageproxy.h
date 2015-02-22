#ifndef IMAGEPROXY_H
#define IMAGEPROXY_H
#include <QImage>
#include <QLineF>
#include <QPainter>
#include <mutex>

/**
 * @brief The ImageProxy class needed to use qimage concurrently in the context we need
 */
class ImageProxy
{
public:
    ImageProxy(QSize s);
    void resetImage(const QSize& s);
    void paintOnImage(QLineF& line, QPen &pen);
    void paintImage(QPainter& painter);
    ~ImageProxy();
private:
    QImage _image;
    std::mutex _imageMutex;
};

#endif // IMAGEPROXY_H
