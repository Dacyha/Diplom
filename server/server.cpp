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
    nextBlockSize = 0;
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
        /*
        qDebug() << "Read...";
        QString str;
        in >> str;
        qDebug() << str;
        SendToClient(str);*/
        for(;;) //бесконечный цикл брух
        {
            if(nextBlockSize == 0)// размер блока не известен
            {
                qDebug() << "nextBlockSize = 0";
                if(socket->bytesAvailable() < 2)//для чтения доступно не меньше 2 байт
                {
                    qDebug() << "Data < 2, break";
                    break;
                }
                in >> nextBlockSize;// размер блока
                qDebug() << "nextBlockSize" << nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)// размер блока сравнивается с кол-вом байт от сервака
            {
                qDebug() << "Data not full, break";
                break;
            }
            QString str;
            QTime time;
            in >> time >>str;
            nextBlockSize = 0;
            qDebug() << str;
            SendToClient(str);
            break;
        }
    }
    else
    {
        qDebug() << "DataStream error";
    }
}

void Server::SendToClient(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
   // socket->write(Data);
    for(int i = 0; i < Sockets.size(); i++)
    {
        Sockets[i]->write(Data);
    }
}
