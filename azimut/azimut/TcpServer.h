#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QBoxLayout>
#include <QLabel>
#include <QString>
#include <QTime>
#include <QProgressBar>
#include <QApplication>
#include <QIntValidator>
#include <QFile>

#include <assert.h>
#include "Point.h"
#include "Compass.h"
//-------------------------------------------------------------------------------------------------
class TcpServer : public QWidget
{
    Q_OBJECT
private:
    QTcpServer *m_pTcpServer;
    QTcpSocket *m_pClientSocket;

    QLineEdit *m_ptxtLatitudeDegrees;
    QLineEdit *m_ptxtLatitudeMinutes;
    QLineEdit *m_ptxtLatitudeSeconds;

    QLineEdit *m_ptxtLongitudeDegrees;
    QLineEdit *m_ptxtLongitudeMinutes;
    QLineEdit *m_ptxtLongitudeSeconds;

    QLineEdit *m_ptxtServerPort;
    QProgressBar *m_pProgressBar;
    int m_ProgressBarMax;

    QTextEdit *m_ptxtInfo;
    quint16 m_NextBlockSize;

    Compass *m_pCompas;

    Point m_ServerPoint;
    Point m_ClientPoint;

    double convertToFloatingPointValue(int degs, int mins, int secs);
    void sendToClient(QTcpSocket* pSocket, const QString& str);
public:
    TcpServer(int port, QWidget *pwgt = nullptr);
    ~TcpServer();
protected:
    void closeEvent(QCloseEvent*) override;
    void writeSettings();
    void readSettings();
public slots:
    virtual void slotNewConnection();
    void slotReadClient();
private slots:
    void slotDisplayConnectedState();
    void slotDisplayUnconnectedState();
    void slotListenNewPort();
    void slotCalcAzimutOnClient(const QString& str);
signals:
    void connected();
    void disconnected();
};

#endif // TCPSERVER_H
