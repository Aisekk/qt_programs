#ifndef FILTER_H
#define FILTER_H

#include <QVideoFilterRunnable>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>

class FilterRunnable : public QVideoFilterRunnable
{
public:
    QVideoFrame run(QVideoFrame *pframe, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;
};

class Filter : public QAbstractVideoFilter
{
public:
    QVideoFilterRunnable* createFilterRunnable();
signals:
    void finished(QObject *result);
};


#endif // FILTER_H
