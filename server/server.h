#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include<QTcpSocket>
#include <QVector>
#include<QTime>

class Server : public QTcpServer
{
    Q_OBJECT;

public:
    Server();
    QTcpSocket *socket;
private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    //QString nickNameTest;
    void SendToClient(QString str, QString nickNameTest);
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif // SERVER_H
