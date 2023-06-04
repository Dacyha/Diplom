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
     id = 0;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::disconnectClent);

    qDebug() << "client connected" << socketDescriptor;
}

void Server::slotReadyRead()
{
    socketRead = (QTcpSocket*)sender();
    QDataStream in(socketRead);
    in.setVersion(QDataStream::Qt_5_12);
    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "Read...";
        QString str;
        QTime time;
        QString  readCode;
        in >>  readCode;
        qDebug() << "Read code:" << readCode.toInt()  ;

        switch (readCode.toInt()) {
            case 1:
                in >> nickNameClient;
                qDebug() <<"Client connected: "<< nickNameClient<<" sockets: "<< socketRead;
                BuildClientDB();
                break;
            case 2:
                in >> time >> nickNameClient >> str;
                qDebug()<< "Client send message: " << time  << nickNameClient <<": "<< str << socketRead;
                EditJsonFile(time, nickNameClient, str);
                SendToClient(str);
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

void Server::BuildClientDB()
{
        Clients.insert(nickNameClient, socketRead);
        qDebug() << nickNameClient <<  socketRead;
        SendClientDB();
}

void Server::disconnectClent()
{
    QTcpSocket* clientDisconnect = qobject_cast<QTcpSocket*>(sender());
    if(clientDisconnect)
    {
        clientDisconnect->deleteLater();
        nickNameClient = Clients.key(clientDisconnect);
        qDebug() << "Client disconnected" << nickNameClient <<  socketRead;
        Clients.remove(nickNameClient);
        SendClientDB();
    }
    else
    {
       qDebug() << "Client disconnected error";
    }
}

void Server::SendClientDB()
{
    QString sendCode = "1";
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    if(out.status() == QDataStream::Ok)
    {
       QList<QString> clientTable;
       clientTable.clear();
       clientTable.append(Clients.keys());
       out << sendCode << clientTable;
       foreach(QString nickNameClient, Clients.keys())
        {
            Clients.value(nickNameClient)->write(Data);
        }
        qDebug() << "SendCode:" << sendCode << "update table";
    }
    else
    {
        qDebug() << "DataStream error";
    }
}

void Server::EditJsonFile(QTime time, QString nickNameClient, QString str)
{

    QString dir("C:/Users/" + QDir::home().dirName() + "/Documents/" + QCoreApplication::applicationName()+ "/server");
    if (!QDir(dir).exists())
    {
        QDir().mkdir(dir);
    }

    QFile fileJson(dir + "/messages.json");

        if (fileJson.open(QIODevice::WriteOnly |QIODevice::Append))//если файла нет, он будет создан |QIODevice::Append
{
        QJsonArray  recordObject;
        QJsonArray  recordObjectToFile;
        QJsonObject objObject;
        QJsonObject objObjectToFile;
        id++;
        objObject.insert("id", id);
        objObject.insert("dateTime", time.toString());
        objObject.insert("nickName", nickNameClient);
        objObject.insert("text", str);
        objObjectToFile["texts"] = objObject;
        recordObject.append(objObjectToFile);
        QJsonDocument doc(recordObject);
        fileJson.write(QJsonDocument(doc).toJson(QJsonDocument::Indented));
        fileJson.close();
  }
}

void Server::SendToClient(QString str)
{
    QString sendCode = "2";
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    if(out.status() == QDataStream::Ok)
    {
        out << sendCode << QTime::currentTime() << nickNameClient << str;
        qDebug() << "all sockets: ";

        foreach(QString nickNameClient, Clients.keys())
        {
            Clients.value(nickNameClient)->write(Data);
            qDebug() << Clients.value(nickNameClient);
        }
    }
    else
    {
        qDebug() << "DataStream error";
    }
}
