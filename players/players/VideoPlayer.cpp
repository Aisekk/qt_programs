#include "VideoPlayer.h"
#include <QVideoWidget>

VideoPlayer::VideoPlayer(QWidget *pwgt) : SoundPlayer(pwgt)
{
    QVideoWidget *pvw = new QVideoWidget;
    pvw->setMinimumSize(300, 300);

    m_pvbxMainLayout->addWidget(pvw);
    m_pmp->setVideoOutput(pvw);
}
