#include "server.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any, 8888))
    {
        qDebug() << "Start";
    }
    else
    {
        qDebug() << "error Start";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    qDebug() << "client connected" << socketDescriptor;
}

void Server::slotReadyRead()
{
    socketRead = (QTcpSocket*)sender();
    //QByteArray  readCode = socket->read(6);
    //qDebug() << readCode.toInt();
    QDataStream in(socketRead);
    in.setVersion(QDataStream::Qt_6_5);
    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "Read...";
        QString str;
        QTime time;
        QString nickNameClient;
        QString  readCode;
        in >>  readCode;
        qDebug() << "Read code:" << readCode.toInt()  ;

        switch (readCode.toInt()) {
            case 1:
                in >> nickNameClient;
                qDebug() <<"Client connected: "<< nickNameClient<<" sockets: "<< socketRead;
                BuildClientDB(nickNameClient);
                break;
            case 2:
                in >> time >> nickNameClient >> str;
                qDebug()<< "Client send message: " << time  << nickNameClient <<": "<< str << socketRead;
                SendToClient(str, nickNameClient);
                break;
            default:
                qDebug() << "slotReadyRead Error";
                break;
            }
    }
    else
    {
        qDebug() << "DataStream error";
    }
}

void Server::BuildClientDB(QString nickNameClient)
{
        QMap<QString, QTcpSocket*> Clients;
        Clients.insert(nickNameClient, socketRead);
        qDebug() << "QMap v dorabotke"<< nickNameClient <<  socketRead;
}

void Server::SendToClient(QString str, QString nickNameClient)
{
   QString sendCode = "2";
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    if(out.status() == QDataStream::Ok)
    {
        out << sendCode << QTime::currentTime() << nickNameClient << str;
        qDebug() << "all sockets: ";
        for(int i = 0; i < Sockets.size(); i++)
        {
            Sockets[i]->write(Data);
            qDebug() << i <<" socket: "<< Sockets[i];
        }
    }
    else
    {
    qDebug() << "DataStream error";
    }
}
