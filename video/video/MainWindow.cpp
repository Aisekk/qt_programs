#include "MainWindow.h"

MainWindow::MainWindow(QWidget *pwgt)
    : QMainWindow(pwgt)
{
    m_pToolBar = new QToolBar("Панель инструментов", this);
    m_pPopUpWgt = new PopUpWidget("Панель настроек", this);
    m_pVideoWidget = new VideoWidget(this);
    //-------------------------------------------------------------------------------------------------
    QMediaPlayer *pPlayer = m_pVideoWidget->mediaPlayer();
    //QVideoWidget *pVideoWidget = m_pVideoWidget->videoWidget();
    //m_pVideoSurface = new VideoSurface(pVideoWidget, this);
    //m_pVideoProducer = new VideoProducer(this);
    //m_pVideoProducer->setVideoSurface(m_pVideoSurface);

    //QAbstractVideoSurface* psurface = m_pVideoProducer->videoSurface();
    //pPlayer->setVideoOutput(m_pVideoSurface);

    //-------------------------------------------------------------------------------------------------
    m_pProbe = new QVideoProbe(this);
    connect(m_pProbe, SIGNAL(videoFrameProbed(QVideoFrame)), SLOT(slotProcessFrame(QVideoFrame)));
    if(m_pProbe->setSource(pPlayer)) qDebug() << "set source";
    m_pFilterRunnable = new FilterRunnable;

    connect(this, SIGNAL(frameAvailable(QImage&)), SLOT(slotProcessFrame(QImage&)));
    //-------------------------------------------------------------------------------------------------
    m_pRecorder = new QMediaRecorder(pPlayer);
    connect(m_pRecorder, SIGNAL(stateChanged(QMediaRecorder::State)), SLOT(slotRecord(QMediaRecorder::State)));

//    QAudioEncoderSettings audioSettings;
//    audioSettings.setCodec("audio/amr");
//    audioSettings.setQuality(QMultimedia::LowQuality);
//    m_pRecorder->setAudioSettings(audioSettings);

    QVideoEncoderSettings settings = m_pRecorder->videoSettings();
    //settings.setCodec("video/mpg");
    settings.setResolution(640,480);
    settings.setQuality(QMultimedia::LowQuality);
    settings.setFrameRate(30.0);

    m_pRecorder->setVideoSettings(settings);

    connect(m_pRecorder, SIGNAL(statusChanged(QMediaRecorder::Status)),
            SLOT(slotRecordStatus(QMediaRecorder::Status)));
    connect(m_pRecorder, SIGNAL(stateChanged(QMediaRecorder::State)),
            SLOT(slotRecordState(QMediaRecorder::State)));
    connect(m_pRecorder, SIGNAL(error(QMediaRecorder::Error)),
            SLOT(slotRecordError(QMediaRecorder::Error)));
    //-------------------------------------------------------------------------------------------------
    QIcon openIcon(":/filesave.png");
    m_pactSave = new QAction("Запись", nullptr);
    m_pactSave->setText("&Запись ...");
    m_pactSave->setShortcut(QKeySequence("CTRL+S"));
    m_pactSave->setToolTip("Запись");
    m_pactSave->setIcon(openIcon);
    m_pactSave->setIconVisibleInMenu(true);
    m_pactSave->setVisible(true);
    connect(m_pactSave, SIGNAL(triggered()), SLOT(slotRecordFile()));
    //-------------------------------------------------------------------------------------------------
    m_pToolBar->addAction(m_pactSave);
    m_pPopUpWgt->addAction(m_pactSave);
    addToolBar(Qt::TopToolBarArea, m_pToolBar);
    addToolBarBreak();
    addToolBar(Qt::TopToolBarArea, m_pPopUpWgt);

    //компоновка центрального виджета
    m_pvbxLayout = new QVBoxLayout;
    m_pvbxLayout->addWidget(m_pVideoWidget);

    m_pMDI = new QMdiArea;
    m_pMDI->setLayout(m_pvbxLayout);
    m_pMDI->setVisible(true);
    setCentralWidget(m_pMDI);
    setMaximumSize(700, 450);
}
MainWindow::~MainWindow(){  }
void MainWindow::closeEvent(QCloseEvent*)
{
    QMediaPlayer *pPlayer = m_pVideoWidget->mediaPlayer();
    pPlayer->stop();
    //m_pProbe->flush();
    //qApp->processEvents();
    //delete m_pProbe;
}
//-------------------------------------------------------------------------------------------------
void MainWindow::slotProcessFrame(const QVideoFrame& frame)
{
    if(frame.isValid())
    {
        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::WriteOnly);
        QImage image(cloneFrame.bits(),
                     cloneFrame.width(),
                     cloneFrame.height(),
                     QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat()));
        //image.save("clone","JPG", 100);
        QVideoWidget *pVideoWidget = m_pVideoWidget->videoWidget();
//        VideoSurface *pSurface = new VideoSurface(pVideoWidget, this);
//        QMediaPlayer *pPlayer = m_pVideoWgt->mediaPlayer();
//        pPlayer->setVideoOutput(pSurface);

        //emit frameAvailable(image); // this is very important
        cloneFrame.unmap();


        QVideoFrame& f = const_cast<QVideoFrame&>(frame);
        QVideoFrame *pframe = &f;
        m_currentFrame = frame;

        QVideoSurfaceFormat vsf(QSize(frame.width(), frame.height()), frame.pixelFormat());
        //static int i = 0;
        //if(i == 200) i = 0;
        //vsf.setFrameSize(abs(frame.width() - i), abs(frame.height() - i));
        m_pFilterRunnable->run(pframe, vsf, QVideoFilterRunnable::LastInChain);
        //++i;
        pVideoWidget->update();
    }

//    QVideoFrame& frame = const_cast<QVideoFrame&>(fr);
//    if(frame.isValid())
//    {
//        //int width = frame.width();
//        //int height = frame.height();

//        if(frame.map(QAbstractVideoBuffer::WriteOnly))
//        {
//            uchar* pStart = frame.bits();
//            if(pStart)
//            {
//                int bytesCount = frame.mappedBytes();
//                uchar* pEnd = pStart + bytesCount;
//                for(uchar* p = pStart; p != pEnd; ++p)
//                {
//                    *p = 'a';
//                }
//            }
//        }
//        frame.unmap();
//    }
    //qDebug() << "process frame";
}
void MainWindow::slotProcessFrame(QImage& image)
{
    //image.save(fileName,"JPG",100);
    qDebug() << "Get image";
}
//-------------------------------------------------------------------------------------------------
void MainWindow::slotRecord(QMediaRecorder::State state)
{
    if(state == QMediaRecorder::RecordingState)
        m_pRecorder->record();
    else qDebug() << "does not start record";
}
void MainWindow::slotRecordFile()
{
    QStringList videoCodecs = m_pRecorder->supportedVideoCodecs();
    for(auto& str : videoCodecs) qDebug() << str;

    QString fileName = QFileDialog::getSaveFileName(this, "Записать видеопоток", "",
                                                    "video files (*.avi *.mpg)" );
    if(!fileName.isEmpty())
    {

        //if(m_pProbe->setSource(m_pRecorder)) qDebug() << "Recorder set";
        QMediaPlayer *pmp = m_pVideoWidget->mediaPlayer();
        //QMediaPlayer* pmo = qobject_cast<QMediaPlayer*>(_pRecorder->mediaObject());
        if(m_pRecorder->isAvailable())
            qDebug() << "Recorder is available";

        switch (m_pRecorder->availability()) {
        case QMultimedia::Available:
        { qDebug() << "The service is operating correctly."; break; }
        case QMultimedia::ServiceMissing:
        { qDebug() << "There is no service available to provide the requested functionality."; break; }
        case QMultimedia::ResourceError:
        { qDebug() << "The service could not allocate resources required to function correctly."; break; }
        case QMultimedia::Busy:
        { qDebug() << "The service must wait for access to necessary resources."; break; }
        default:{ qDebug() << "Unknown error"; break; }
        }

        switch (m_pRecorder->error()) {
        case QMediaRecorder::NoError:{ qDebug() << "No Errors."; break; }
        case QMediaRecorder::ResourceError:{ qDebug() << "Device is not ready or not available."; break; }
        case QMediaRecorder::FormatError:{ qDebug() << "Current format is not supported."; break; }
        case QMediaRecorder::OutOfSpaceError:{ qDebug() << "No space left on device."; break; }
        default:{ qDebug() << "Unknown error"; break; }
        }

        if(pmp)
        {
            if(m_pRecorder->setOutputLocation(QUrl::fromLocalFile(fileName))) qDebug() << "location set";
            if(pmp->isVideoAvailable())  m_pRecorder->record();
            else qDebug() << "video unavailable";

            switch (m_pRecorder->status()) {
            case QMediaRecorder::UnavailableStatus:
            { qDebug() << "The recorder is not available or not supported by connected media object."; break; }
            case QMediaRecorder::UnloadedStatus:
            { qDebug() << "The recorder is available but not loaded."; break; }
            case QMediaRecorder::LoadingStatus:
            { qDebug() << "The recorder is initializing."; break; }
            case QMediaRecorder::LoadedStatus:
            { qDebug() << "The recorder is initialized and ready to record media."; break; }
            case QMediaRecorder::StartingStatus:
            { qDebug() << "Recording is requested but not active yet."; break; }
            case QMediaRecorder::RecordingStatus:
            { qDebug() << "Recording is active."; break; }
            case QMediaRecorder::PausedStatus:
            { qDebug() << "Recording is paused."; break; }
            case QMediaRecorder::FinalizingStatus:
            { qDebug() << "Recording is stopped with media being finalized."; break; }
            default:{ qDebug() << "Unknown status"; break; }
            }

            //m_pRecorder->stop();
        }

    }
}
void MainWindow::slotRecordStatus(QMediaRecorder::Status status)
{
    switch (status) {
    case QMediaRecorder::UnavailableStatus:
    { qDebug() << "The recorder is not available or not supported by connected media object."; break; }
    case QMediaRecorder::UnloadedStatus:
    { qDebug() << "The recorder is available but not loaded."; break; }
    case QMediaRecorder::LoadingStatus:
    { qDebug() << "The recorder is initializing."; break; }
    case QMediaRecorder::LoadedStatus:
    { qDebug() << "The recorder is initialized and ready to record media."; break; }
    case QMediaRecorder::StartingStatus:
    { qDebug() << "Recording is requested but not active yet."; break; }
    case QMediaRecorder::RecordingStatus:
    { qDebug() << "Recording is active."; break; }
    case QMediaRecorder::PausedStatus:
    { qDebug() << "Recording is paused."; break; }
    case QMediaRecorder::FinalizingStatus:
    { qDebug() << "Recording is stopped with media being finalized."; break; }
    default:{ qDebug() << "Unknown status"; break; }
    }
}
void MainWindow::slotRecordState(QMediaRecorder::State state)
{
    switch (state) {
    case QMediaRecorder::StoppedState:{ qDebug() << "The recorder is not active."; break; }
    case QMediaRecorder::RecordingState:{ qDebug() << "The recording is requested."; break; }
    case QMediaRecorder::PausedState:{ qDebug() << "The recorder is paused."; break; }
    default:{ qDebug() << "Unknown state"; break; }
    }
}
void MainWindow::slotRecordError(QMediaRecorder::Error error)
{
    switch (error) {
    case QMediaRecorder::NoError:{ qDebug() << "No Errors."; break; }
    case QMediaRecorder::ResourceError:{ qDebug() << "Device is not ready or not available."; break; }
    case QMediaRecorder::FormatError:{ qDebug() << "No Errors."; break; }
    case QMediaRecorder::OutOfSpaceError:{ qDebug() << "No space left on device."; break; }
    default:{ qDebug() << "Unknown error"; break; }
    }
}
//-------------------------------------------------------------------------------------------------
