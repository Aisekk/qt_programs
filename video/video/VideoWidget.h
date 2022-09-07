#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QStyle>
#include <QFileDialog>
#include <QTime>
#include <QVideoWidget>

#include "VideoSurface.h"

class VideoWidget : public QWidget
{
    Q_OBJECT
protected:
    QMediaPlayer *m_pPlayer;
    QVideoWidget *m_pVideoWidget;
    VideoSurface *m_pVideoSurface;
    QVBoxLayout *m_pvbxMainLayout;
private:
    QPushButton *m_pcmdPlay;
    QPushButton *m_pcmdStop;
    QSlider *m_psldPosition;
    QLabel *m_plblCurrent;
    QLabel *m_plblRemain;

    QString msecsToString(qint64 n);
public:
    VideoWidget(QWidget *pwgt = nullptr);
    ~VideoWidget();
    QMediaPlayer* mediaPlayer() const;
    QVideoWidget* videoWidget() const;
private slots:
    void slotOpen();
    void slotPlay();
    void slotSetSliderPosition(qint64);
    void slotSetMediaPosition(int);
    void slotSetDuration(qint64);
    void slotStatusChanged(QMediaPlayer::State state);
};

#endif // VIDEOWIDGET_H
