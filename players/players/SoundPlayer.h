#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QStyle>
#include <QFileDialog>
#include <QTime>

class SoundPlayer : public QWidget
{
    Q_OBJECT
protected:
    QMediaPlayer *m_pmp;
    QVBoxLayout *m_pvbxMainLayout;
private:
    QPushButton *m_pcmdPlay;
    QPushButton *m_pcmdStop;
    QSlider *m_psldPosition;
    QLabel *m_plblCurrent;
    QLabel *m_plblRemain;

    QString msecsToString(qint64 n);
public:
    SoundPlayer(QWidget *pwgt = nullptr);
    ~SoundPlayer();
private slots:
    void slotOpen();
    void slotPlay();
    void slotSetSliderPosition(qint64);
    void slotSetMediaPosition(int);
    void slotSetDuration(qint64);
    void slotStatusChanged(QMediaPlayer::State state);
};

#endif // SOUNDPLAYER_H
