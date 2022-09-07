#include "VideoWidget.h"

VideoWidget::VideoWidget(QWidget *pwgt) : QWidget(pwgt)
{
    QPushButton *pcmdOpen = new QPushButton("&Открыть");
    QSlider *psldVolume = new QSlider;

    m_pcmdPlay = new QPushButton;
    m_pcmdStop = new QPushButton;;
    m_psldPosition = new QSlider;
    m_plblCurrent = new QLabel(msecsToString(0));
    m_plblRemain = new QLabel(msecsToString(0));
    m_pPlayer = new QMediaPlayer(this);

    m_pcmdPlay->setEnabled(false);
    m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    m_pcmdStop->setEnabled(false);
    m_pcmdStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    m_psldPosition->setRange(0,0);
    m_psldPosition->setOrientation(Qt::Horizontal);

    psldVolume->setRange(0, 100);
    int DefaultVolume = 50;
    m_pPlayer->setVolume(DefaultVolume);
    psldVolume->setValue(DefaultVolume);
    psldVolume->setMaximumHeight(50);

    connect(pcmdOpen, SIGNAL(clicked()), SLOT(slotOpen()));
    connect(m_pcmdPlay, SIGNAL(clicked()), SLOT(slotPlay()));
    connect(m_pcmdStop, SIGNAL(clicked()), m_pPlayer, SLOT(stop()));
    connect(psldVolume, SIGNAL(valueChanged(int)), m_pPlayer, SLOT(setVolume(int)));

    connect(m_psldPosition, SIGNAL(sliderMoved(int)), SLOT(slotSetMediaPosition(int)));
    connect(m_pPlayer, SIGNAL(positionChanged(qint64)), SLOT(slotSetSliderPosition(qint64)));
    connect(m_pPlayer, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));
    connect(m_pPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(slotStatusChanged(QMediaPlayer::State)));

    QHBoxLayout *phbxPlayControls = new QHBoxLayout;
    phbxPlayControls->addWidget(pcmdOpen);
    phbxPlayControls->addWidget(m_pcmdPlay);
    phbxPlayControls->addWidget(m_pcmdStop);
    phbxPlayControls->addWidget(psldVolume);

    QHBoxLayout *phbxTimeControls = new QHBoxLayout;
    phbxTimeControls->addWidget(m_plblCurrent);
    phbxTimeControls->addWidget(m_psldPosition);
    phbxTimeControls->addWidget(m_plblRemain);

    m_pvbxMainLayout = new QVBoxLayout;

    m_pVideoWidget = new QVideoWidget;
    m_pVideoWidget->setMinimumSize(300, 300);
    m_pVideoWidget->setMaximumSize(600, 600);
    m_pvbxMainLayout->addWidget(m_pVideoWidget);

    m_pVideoSurface = new VideoSurface(m_pVideoWidget, this);
    connect(m_pcmdStop, SIGNAL(clicked()), m_pVideoSurface, SLOT(slotStop()));

    m_pPlayer->setVideoOutput(m_pVideoSurface);

    m_pvbxMainLayout->addLayout(phbxPlayControls);
    m_pvbxMainLayout->addLayout(phbxTimeControls);

    setLayout(m_pvbxMainLayout);
}
VideoWidget::~VideoWidget(){}
QMediaPlayer* VideoWidget::mediaPlayer() const{ return m_pPlayer; }
QVideoWidget* VideoWidget::videoWidget() const{ return m_pVideoWidget; }
//-------------------------------------------------------------------------------------------------
QString VideoWidget::msecsToString(qint64 n)
{
    int hours = (n / (60*60*1000));
    int minutes = ((n % (60*60*1000)) / (60*1000));
    int seconds = ((n % (60*1000)) / 1000);
    return QTime(hours, minutes, seconds).toString("hh:mm:ss");
}
//-------------------------------------------------------------------------------------------------
void VideoWidget::slotOpen()
{
    QString file = QFileDialog::getOpenFileName(this, "Открыть файл");
    if(!file.isEmpty())
    {
        m_pPlayer->setMedia(QUrl::fromLocalFile(file));
        m_pcmdPlay->setEnabled(true);
        m_pcmdStop->setEnabled(true);
    }
}
void VideoWidget::slotPlay()
{
    switch (m_pPlayer->state()) {
    case QMediaPlayer::PlayingState:{ m_pPlayer->pause(); break; }
    default:{ m_pPlayer->play();
        QVideoSurfaceFormat vsf = m_pVideoSurface->surfaceFormat();
        m_pVideoSurface->start(vsf); break; }
    }
}
void VideoWidget::slotSetSliderPosition(qint64 n)
{
    m_psldPosition->setValue(n);

    m_plblCurrent->setText(msecsToString(n));
    int duration = m_psldPosition->maximum();
    m_plblRemain->setText(msecsToString(duration - n));
}
void VideoWidget::slotSetMediaPosition(int n)
{
    m_pPlayer->setPosition(n);
}
void VideoWidget::slotSetDuration(qint64 n)
{
    m_psldPosition->setRange(0,n);
    m_plblCurrent->setText(msecsToString(0));
    m_plblRemain->setText(msecsToString(n));
}
void VideoWidget::slotStatusChanged(QMediaPlayer::State state)
{
    switch (state) {
    case QMediaPlayer::PlayingState:
    { m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPause)); break; }
    default:{ m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay)); break; }
    }
}
//-------------------------------------------------------------------------------------------------
