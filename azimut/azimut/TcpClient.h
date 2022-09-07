#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QString>
#include <QTime>
#include <QProgressBar>
#include <QApplication>
#include <QHostAddress>
#include <QIntValidator>
#include <QFile>

class TcpClient : public QWidget
{
    Q_OBJECT
private:
    QTcpSocket *m_pTcpSocket;

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

    double convertToFloatingPointValue(int degs, int mins, int secs) const;
    double calcLatitude() const;
    double calcLongitude() const;
    std::pair<double, double> calcPoint(int value, const QString& lineEditName) const;
public:
    TcpClient(const QString& host, int port, QWidget *pwgt = nullptr);
    ~TcpClient();
protected:
    void closeEvent(QCloseEvent*) override;
    void writeSettings();
    void readSettings();
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotSendToServer(const QString& str);
    void slotConnected();
    void slotDisplayConnectionState(QAbstractSocket::SocketState);
    void slotConnectToNewPort();
};

#endif // TCPCLIENT_H
