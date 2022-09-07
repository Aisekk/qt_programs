#ifndef VIDEOPRODUCER_H
#define VIDEOPRODUCER_H

#include <QObject>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>

class VideoProducer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)
public:
    explicit VideoProducer(QObject *parent = nullptr);  
    QAbstractVideoSurface* videoSurface() const;
    void setVideoSurface(QAbstractVideoSurface *surface);
    void setVideoSurfaceFormat(const QVideoSurfaceFormat& format);
public slots:
    void frameReceived(const QVideoFrame &frame);
private:
    QAbstractVideoSurface *m_surface;
    QVideoSurfaceFormat m_format;
};

#endif // VIDEOPRODUCER_H
