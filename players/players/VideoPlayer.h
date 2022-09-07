#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "SoundPlayer.h"

class VideoPlayer : public SoundPlayer
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *pwgt = nullptr);

signals:

public slots:
};

#endif // VIDEOPLAYER_H
