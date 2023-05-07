#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include<QTcpSocket>
#include<QTime>
#include <QMap>

class Server : public QTcpServer
{
    Q_OBJECT;

public:
    Server();
    QTcpSocket *socketRead;
    QTcpSocket *socket;
private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    QMap<QString, QTcpSocket*> Clients;
    QString nickNameClient;
    void SendToClient(QString str);
    void BuildClientDB();
    void SendClientDB();
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
    void disconnectClent();
};

#endif // SERVER_H
