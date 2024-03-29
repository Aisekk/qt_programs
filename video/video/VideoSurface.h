#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QList>
#include <QWidget>
#include <QPainter>
#include <QVideoWidget>

class VideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    VideoSurface(QVideoWidget *pwgt, QObject *parent = nullptr);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    bool isFormatSupported(const QVideoSurfaceFormat &format) const;

    bool start(const QVideoSurfaceFormat &format);
    void stop();

    bool present(const QVideoFrame &frame);

    QRect videoRect() const { return targetRect; }
    void updateVideoRect();

    void paint(QPainter *painter);
public slots:
    void slotStop();
private:
    QVideoWidget *m_pVideoWidget;
    QImage::Format imageFormat;
    QRect targetRect;
    QSize imageSize;
    QRect sourceRect;
    QVideoFrame currentFrame;

signals:
    void frameAvailable(QImage frame);
};

#endif // VIDEOSURFACE_H
