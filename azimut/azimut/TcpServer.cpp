#include "TcpServer.h"

TcpServer::TcpServer(int port, QWidget *pwgt)
    : QWidget(pwgt), m_pClientSocket{}, m_ProgressBarMax(100), m_NextBlockSize(0),
      m_ServerPoint{}, m_ClientPoint{}
{
    setWindowTitle("Сервер: " + QString::number(port));
    setMaximumSize(250, 600);
    m_pTcpServer = new QTcpServer(this);
    //---------------------------------------------------------------------------------------------
    m_pProgressBar = new QProgressBar;
    m_pProgressBar->setMinimum(0);
    m_pProgressBar->setMaximum(m_ProgressBarMax);
    m_pProgressBar->setValue(0);
    m_pProgressBar->setTextVisible(false);
    //---------------------------------------------------------------------------------------------
    if(!m_pTcpServer->listen(QHostAddress::Any, port))
    {
        QMessageBox::critical(nullptr, "Ошибка сервера",
                              "Не удалось запустить сервер: " + m_pTcpServer->errorString());
        m_pTcpServer->close();
        return;
    }
    connect(m_pTcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    connect(this, SIGNAL(connected()), this, SLOT(slotDisplayConnectedState()));
    //---------------------------------------------------------------------------------------------
    QVBoxLayout *pvbxLayout = new QVBoxLayout;
    QGridLayout *pgrdLayout = new QGridLayout;
    //---------------------------------------------------------------------------------------------
    pgrdLayout->addWidget(new QLabel("Градусов"), 0, 1);
    pgrdLayout->addWidget(new QLabel("Минут"), 0, 2);
    pgrdLayout->addWidget(new QLabel("Секунд"), 0, 3);
    //---------------------------------------------------------------------------------------------
    pgrdLayout->addWidget(new QLabel("Широта"), 1, 0);

    m_ptxtLatitudeDegrees = new QLineEdit;
    m_ptxtLatitudeDegrees->setObjectName("LatitudeDegrees");
    m_ptxtLatitudeDegrees->setValidator(new QIntValidator);
    connect(m_ptxtLatitudeDegrees, SIGNAL(textChanged(QString)), SLOT(slotCalcAzimutOnClient(QString)));
    pgrdLayout->addWidget(m_ptxtLatitudeDegrees, 1, 1);

    m_ptxtLatitudeMinutes = new QLineEdit;
    m_ptxtLatitudeMinutes->setObjectName("LatitudeMinutes");
    m_ptxtLatitudeMinutes->setValidator(new QIntValidator);
    connect(m_ptxtLatitudeMinutes, SIGNAL(textChanged(QString)), SLOT(slotCalcAzimutOnClient(QString)));
    pgrdLayout->addWidget(m_ptxtLatitudeMinutes, 1, 2);

    m_ptxtLatitudeSeconds = new QLineEdit;
    m_ptxtLatitudeSeconds->setObjectName("LatitudeSeconds");
    m_ptxtLatitudeSeconds->setValidator(new QIntValidator);
    connect(m_ptxtLatitudeSeconds, SIGNAL(textChanged(QString)), SLOT(slotCalcAzimutOnClient(QString)));
    pgrdLayout->addWidget(m_ptxtLatitudeSeconds, 1, 3);
    //---------------------------------------------------------------------------------------------
    pgrdLayout->addWidget(new QLabel("Долгота"), 2, 0);

    m_ptxtLongitudeDegrees = new QLineEdit;
    m_ptxtLongitudeDegrees->setObjectName("LongitudeDegrees");
    m_ptxtLongitudeDegrees->setValidator(new QIntValidator);
    connect(m_ptxtLongitudeDegrees, SIGNAL(textChanged(QString)), SLOT(slotCalcAzimutOnClient(QString)));
    pgrdLayout->addWidget(m_ptxtLongitudeDegrees, 2, 1);

    m_ptxtLongitudeMinutes = new QLineEdit;  
    m_ptxtLongitudeMinutes->setObjectName("LongitudeMinutes");
    m_ptxtLongitudeMinutes->setValidator(new QIntValidator);
    connect(m_ptxtLongitudeMinutes, SIGNAL(textChanged(QString)), SLOT(slotCalcAzimutOnClient(QString)));
    pgrdLayout->addWidget(m_ptxtLongitudeMinutes, 2, 2);

    m_ptxtLongitudeSeconds = new QLineEdit;    
    m_ptxtLongitudeSeconds->setObjectName("LongitudeSeconds");
    m_ptxtLongitudeSeconds->setValidator(new QIntValidator);
    connect(m_ptxtLongitudeSeconds, SIGNAL(textChanged(QString)), SLOT(slotCalcAzimutOnClient(QString)));
    pgrdLayout->addWidget(m_ptxtLongitudeSeconds, 2, 3);
    //---------------------------------------------------------------------------------------------
    pgrdLayout->addWidget(new QLabel("Порт сервера"), 3, 0);
    m_ptxtServerPort = new QLineEdit;
    m_ptxtServerPort->setValidator(new QIntValidator);
    connect(m_ptxtServerPort, SIGNAL(returnPressed()), SLOT(slotListenNewPort()));
    pgrdLayout->addWidget(m_ptxtServerPort, 3, 1);
    //---------------------------------------------------------------------------------------------
    pvbxLayout->addLayout(pgrdLayout);
    //---------------------------------------------------------------------------------------------
    m_ptxtInfo = new QTextEdit;
    m_ptxtInfo->setReadOnly(true);
    m_pCompas = new Compass;
    //---------------------------------------------------------------------------------------------
    pvbxLayout->addWidget(m_pProgressBar);
    pvbxLayout->addWidget(m_ptxtInfo);
    pvbxLayout->addWidget(m_pCompas);
    setLayout(pvbxLayout);
    //---------------------------------------------------------------------------------------------
    readSettings();
}
TcpServer::~TcpServer(){}
void TcpServer::closeEvent(QCloseEvent*)
{
    if(m_pClientSocket->state() == QAbstractSocket::ConnectedState)
        m_pClientSocket->disconnectFromHost();
    m_pTcpServer->close();
    writeSettings();
}
void TcpServer::writeSettings()
{
    QFile file("server_coordinates.txt");
    QTextStream out(&file);

    if(file.open(QFile::WriteOnly | QFile::Truncate))
    {
        out << m_ptxtLatitudeDegrees->text() << '\t'
            << m_ptxtLatitudeMinutes->text() << '\t'
            << m_ptxtLatitudeSeconds->text() << "\r\n"
            << m_ptxtLongitudeDegrees->text() << '\t'
            << m_ptxtLongitudeMinutes->text() << '\t'
            << m_ptxtLongitudeSeconds->text() << "\r\n";
        file.close();
    }
}
void TcpServer::readSettings()
{
    QFile file("server_coordinates.txt");
    QTextStream in(&file);
    QString line;
    QStringList list;

    if(file.open(QFile::ReadOnly))
    {
        line = in.readLine();
        list = line.split('\t');
        m_ptxtLatitudeDegrees->setText(list[0]);
        m_ptxtLatitudeMinutes->setText(list[1]);
        m_ptxtLatitudeSeconds->setText(list[2]);

        line = in.readLine();
        list = line.split('\t');
        m_ptxtLongitudeDegrees->setText(list[0]);
        m_ptxtLongitudeMinutes->setText(list[1]);
        m_ptxtLongitudeSeconds->setText(list[2]);
        file.close();
    }

    int degs = (m_ptxtLatitudeDegrees->text()).toInt();
    int mins = (m_ptxtLatitudeMinutes->text()).toInt();
    int secs = (m_ptxtLatitudeSeconds->text()).toInt();
    double latitude = convertToFloatingPointValue(degs, mins, secs);
    m_ServerPoint.setLatitude(latitude);

    degs = (m_ptxtLongitudeDegrees->text()).toInt();
    mins = (m_ptxtLongitudeMinutes->text()).toInt();
    secs = (m_ptxtLongitudeSeconds->text()).toInt();
    double longitude = convertToFloatingPointValue(degs, mins, secs);
    m_ServerPoint.setLongitude(longitude);

    double clientLat = m_ClientPoint.latitude();
    double clientLon = m_ClientPoint.longitude();
    double clientAzimut = m_ServerPoint.azimuth(clientLat, clientLon);
    m_pCompas->setAzimut(clientAzimut);
}
//-------------------------------------------------------------------------------------------------
double TcpServer::convertToFloatingPointValue(int degs, int mins, int secs)
{
    double seconds = (double)(secs/60.0);
    double minutes = (double)(mins/60.0) + seconds;
    double degrees = (double)degs + minutes;
    return degrees;
}
void TcpServer::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}
//-------------------------------------------------------------------------------------------------
void TcpServer::slotNewConnection()
{
    QTcpSocket *pClientSocket = m_pTcpServer->nextPendingConnection();
    if(pClientSocket) emit connected();
    m_pClientSocket = pClientSocket;
    connect(pClientSocket, SIGNAL(disconnected()), this, SLOT(slotDisplayUnconnectedState()));
    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    sendToClient(pClientSocket, "Сервер: соединение установлено.");
}
void TcpServer::slotReadClient()
{
    QTcpSocket *pClientSocket = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_9);
    for(;;)
    {
        if(!m_NextBlockSize){
            if(pClientSocket->bytesAvailable() < sizeof(quint16)) break;
            in >> m_NextBlockSize;
        }
        if(pClientSocket->bytesAvailable() < m_NextBlockSize) break;
        //-----------------------------------------------------------------------------------------
        double latitude;
        double longitude;
        in >> latitude >> longitude;
        m_ClientPoint.setLatitude(latitude);
        m_ClientPoint.setLongitude(longitude);
        //-----------------------------------------------------------------------------------------
        double clientAzimut = m_ServerPoint.azimuth(latitude, longitude);
        m_pCompas->setAzimut(clientAzimut);
        //-----------------------------------------------------------------------------------------
        QString message = "Клиент отправил - " + QString::number(latitude) + "_" +
                QString::number(longitude);
        m_ptxtInfo->append(message);
        //-----------------------------------------------------------------------------------------
        m_NextBlockSize = 0;
        sendToClient(pClientSocket, "Сервер: получено \"" +
                     QString::number(latitude) + "_" + QString::number(longitude) + "\"");
    }
}
//-------------------------------------------------------------------------------------------------
void TcpServer::slotDisplayConnectedState()
{
        for(int i = 0; i < m_ProgressBarMax; ++i)
        {
            m_pProgressBar->setValue(i);
            qApp->processEvents();
        }
}
void TcpServer::slotDisplayUnconnectedState()
{
    m_pProgressBar->setValue(0);
}
void TcpServer::slotListenNewPort()
{
    QLineEdit *ptxtServerPort = qobject_cast<QLineEdit*>(sender());
    quint16 port{};
    if(ptxtServerPort) port = (ptxtServerPort->text()).toUShort();

    if(port)
    {
        if(m_pClientSocket->state() == QAbstractSocket::UnconnectedState)
            qDebug() << "Server: Client socket is not connected ";

        if(port != m_pTcpServer->serverPort())
        {
            //сначала проверка
            if(m_pClientSocket->state() == QAbstractSocket::ConnectedState)
                m_pClientSocket->disconnectFromHost();
            m_pTcpServer->close();

            if(!m_pTcpServer->listen(QHostAddress("localhost"), port))
            {
                QMessageBox::critical(nullptr, "Ошибка сервера",
                                      "Не удалось запустить сервер: " + m_pTcpServer->errorString());
                m_pTcpServer->close();
                return;
            }
            if(!m_pTcpServer->isListening()) qDebug() << "Server is not listening ";
        }

        if(m_pClientSocket->state() == QAbstractSocket::ConnectedState)
            qDebug() << "Server: The connection is established ";

        setWindowTitle("Сервер: " + QString::number(m_pTcpServer->serverPort()));
    }
}
//-------------------------------------------------------------------------------------------------
void TcpServer::slotCalcAzimutOnClient(const QString& str)
{
    QLineEdit *ptxt = qobject_cast<QLineEdit*>(sender());
    QString lineEditName = ptxt->objectName();

    if(lineEditName == "LatitudeDegrees")
    {
        int degs = str.toInt();
        int mins = (m_ptxtLatitudeMinutes->text()).toInt();
        int secs = (m_ptxtLatitudeSeconds->text()).toInt();
        double latitude = convertToFloatingPointValue(degs, mins, secs);
        m_ServerPoint.setLatitude(latitude);
    }
    else if(lineEditName == "LatitudeMinutes")
    {
        int degs = (m_ptxtLatitudeDegrees->text()).toInt();
        int mins = str.toInt();
        int secs = (m_ptxtLatitudeSeconds->text()).toInt();
        double latitude = convertToFloatingPointValue(degs, mins, secs);
        m_ServerPoint.setLatitude(latitude);
    }
    else if(lineEditName == "LatitudeSeconds")
    {
        int degs = (m_ptxtLatitudeDegrees->text()).toInt();
        int mins = (m_ptxtLatitudeMinutes->text()).toInt();
        int secs = str.toInt();
        double latitude = convertToFloatingPointValue(degs, mins, secs);
        m_ServerPoint.setLatitude(latitude);
    }
    else if(lineEditName == "LongitudeDegrees")
    {
        int degs = str.toInt();
        int mins = (m_ptxtLongitudeMinutes->text()).toInt();
        int secs = (m_ptxtLongitudeSeconds->text()).toInt();
        double longitude = convertToFloatingPointValue(degs, mins, secs);
        m_ServerPoint.setLongitude(longitude);
    }
    else if(lineEditName == "LongitudeMinutes")
    {
        int degs = (m_ptxtLongitudeDegrees->text()).toInt();
        int mins = str.toInt();
        int secs = (m_ptxtLongitudeSeconds->text()).toInt();
        double longitude = convertToFloatingPointValue(degs, mins, secs);
        m_ServerPoint.setLongitude(longitude);
    }
    else if(lineEditName == "LongitudeSeconds")
    {
        int degs = (m_ptxtLongitudeDegrees->text()).toInt();
        int mins = (m_ptxtLongitudeMinutes->text()).toInt();
        int secs = str.toInt();
        double longitude = convertToFloatingPointValue(degs, mins, secs);
        m_ServerPoint.setLongitude(longitude);
    }

    double clientLat = m_ClientPoint.latitude();
    double clientLon = m_ClientPoint.longitude();
    double clientAzimut = m_ServerPoint.azimuth(clientLat, clientLon);
    m_pCompas->setAzimut(clientAzimut);
}

