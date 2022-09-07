#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QMdiArea>
#include <QMediaRecorder>
#include <QCamera>
#include <QVideoProbe>
#include <QApplication>

#include "VideoWidget.h"
#include "PopUpWidget.h"
#include "VideoSurface.h"
#include "VideoProducer.h"
#include "Filter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *pwgt = nullptr);
    ~MainWindow();
private:
    QToolBar *m_pToolBar;
    PopUpWidget *m_pPopUpWgt;
    VideoWidget *m_pVideoWidget;
    QAction *m_pactSave;
    QVBoxLayout *m_pvbxLayout;
    QMdiArea *m_pMDI;

    QVideoProbe *m_pProbe;
    QMediaRecorder *m_pRecorder;
    FilterRunnable *m_pFilterRunnable;
    QVideoFrame m_currentFrame;
    VideoSurface *m_pVideoSurface;
    VideoProducer *m_pVideoProducer;
protected:
    virtual void closeEvent(QCloseEvent *) override;
private slots:
    void slotProcessFrame(const QVideoFrame &frame);
    void slotProcessFrame(QImage& image);

    void slotRecord(QMediaRecorder::State state);
    void slotRecordFile();
    void slotRecordStatus(QMediaRecorder::Status status);
    void slotRecordState(QMediaRecorder::State state);
    void slotRecordError(QMediaRecorder::Error error);
signals:
    void frameAvailable(QImage&);
};

#endif // MAINWINDOW_H
