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
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_5);
    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "Read...";
        QString str;
        QTime time;
        QString nickNameTest;
        in >> time >> nickNameTest >> str;
        qDebug() << nickNameTest <<": "<< str;
        qDebug() << socket;
        SendToClient(str, nickNameTest);
    }
    else
    {
        qDebug() << "DataStream error";
    }
}

void Server::SendToClient(QString str, QString nickNameTest)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << QTime::currentTime() << nickNameTest << str;
   // socket->write(Data);
    for(int i = 0; i < Sockets.size(); i++)
    {
        Sockets[i]->write(Data);
    }
}
