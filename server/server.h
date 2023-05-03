#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include<QTcpSocket>
#include <QVector>
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
    void SendToClient(QString str, QString nickNameClient);
    void BuildClientDB(QString nickNameClient);
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
};

#endif // SERVER_H
