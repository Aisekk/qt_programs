#include "VideoProducer.h"

VideoProducer::VideoProducer(QObject *parent) : QObject(parent){}

QAbstractVideoSurface* VideoProducer::videoSurface() const { return m_surface; }

void VideoProducer::setVideoSurface(QAbstractVideoSurface *surface)
{
    if (m_surface != surface && m_surface && m_surface->isActive()) {
        m_surface->stop();
    }
    m_surface = surface;
    if (m_surface)
        m_surface->start(m_format);
}
void VideoProducer::setVideoSurfaceFormat(const QVideoSurfaceFormat& format)
{
    m_format = format;
}

void VideoProducer::frameReceived(const QVideoFrame &frame)
{
    if (m_surface)
        m_surface->present(frame);
}
