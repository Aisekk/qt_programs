#include "Filter.h"

QVideoFrame FilterRunnable::run(QVideoFrame *pframe, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{
    //Q_UNUSED(pframe);
    //Q_UNUSED(surfaceFormat);
    Q_UNUSED(flags);

    if(pframe->isValid())
    {
        int width = pframe->width();
        int height = pframe->height();

        if(pframe->map(QAbstractVideoBuffer::WriteOnly))
        {
            uchar* pStart = pframe->bits();
            if(pStart)
            {
                //int bytesCount = pframe->mappedBytes();
                uchar* pEnd = pStart + 10;
                for(uchar* p = pStart; p != pEnd; ++p)
                {
                    //if(pframe->isWritable()) qDebug() << "frame is writable";
                    *p = 'a';
                }

            }
        }
        //surfaceFormat.setFrameSize(width - 100, height + 100);
        //surfaceFormat.setFrameRate(20);

        pframe->unmap();
    }

    return QVideoFrame();
}

QVideoFilterRunnable* Filter::createFilterRunnable() { return new FilterRunnable; }
