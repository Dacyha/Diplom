#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include<QTcpSocket>
#include<QTime>
#include <QMap>
#include<QDataStream>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QEvent>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

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
    qint64 id;

    void SendToClient(QString str);
    void BuildClientDB();
    void SendClientDB();
    void EditJsonFile(QTime time, QString nickNameClient, QString str);

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
    void disconnectClent();

};

#endif // SERVER_H
