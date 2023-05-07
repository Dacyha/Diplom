#include "mainwindow_client.h"
#include "ui_mainwindow_client.h"
#include<QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    socket->connectToHost("127.0.0.1", 8888);
}

MainWindow::~MainWindow()
{
    socket->disconnectFromHost();
    delete ui;
}

void MainWindow::SendToServer(QString str, QString myNickName)
{
    QString sendCode = "2";
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    if(out.status() == QDataStream::Ok)
    {
        out << sendCode << QTime::currentTime() << myNickName << str;
        socket->write(Data);
        ui->lineEdit->clear();
    }
    else
    {
         ui->textBrowser->append("read error");
    }
}

void MainWindow::SendToServerNickName(QString myNickName)
{
    QString sendCode = "1";
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    if(out.status() == QDataStream::Ok)
    {
        out << sendCode  << myNickName;
        socket->write(Data);
    }
    else
    {
         ui->textBrowser->append("read error");
    }
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_12);
    if(in.status() == QDataStream::Ok)
    {
        QString str;
        QTime time;
        QString nickNameClient;
        QString readCode;
        qint64 TableSize;
        //qint64 it;
        //QList<QString> oleg;
        QString oleg;
         in >>  readCode;
         switch (readCode.toInt()) {
            case 1:

             in  >>  readCode >> TableSize >> oleg;
             ui->textBrowser->append("code 1");//заменить
             ui->textBrowser->append(oleg);//заменить
/*
             for(auto it=1; it!=TableSize; it++)
             {
                 in >>TableSize >> nickNameClient;
                 ui->textBrowser->append("code 1");//заменить
                 ui->textBrowser->append(nickNameClient);//заменить
             }
                it = 1;
                do{
                  in >>  readCode >> TableSize >> nickNameClient;
                  ui->textBrowser->append("code 1");//заменить
                  ui->textBrowser->append(nickNameClient);//заменит
             } while (it !=TableSize);
                */




                //ui->tableWidget->setRowCount(forTable.keys().size());
                //foreach(QString nickNameClient, forTable.keys())
                //{
                    //Clients.value(nickNameClient)->write(Data);
                    //ui->textBrowser->append(forTable.key(nickNameClient).toStdString());//заменить
                    //QTableWidgetItem *newItem = new QTableWidgetItem();
                    //QString oleg = forTable.key(socket);
                    //newItem->setText(forTable.key(socket));
                    //ui->tableWidget->setItem(0,0, newItem);
                    //qDebug() << Clients.value(nickNameClient);
                //}
                break;
            case 2:
                in >> time >> nickNameClient >> str;
                //QTcpSocket *socketRead = (QTcpSocket*)sender();
                if (myNickName == nickNameClient)
                {
                    ui->textBrowser->append(time.toString() + "\n" + "Я: "+ str+ "\n");
                }
                else if (myNickName != nickNameClient)
                {
                    ui->textBrowser->append(time.toString() + "\n" + nickNameClient +": "+ str+ "\n");
                }
                break;
            default:
                    ui->textBrowser->append("error");//заменить
                break;
         }

    }
    else
    {
         ui->textBrowser->append("read error");
    }
}

void MainWindow::readNickName(QString nick)//с 1-го окна
{
    myNickName=nick;
    SendToServerNickName(myNickName);
    //QMap<QString, QTcpSocket*> forTable;
    //forTable.insert(myNickName, socket);
    //EditTable();
}

void MainWindow::EditTable()
{
    //QTableWidgetItem *newItem = new QTableWidgetItem();
    //QString oleg = forTable.key(socket);
    //newItem->setText(forTable.key(socket));
    //ui->tableWidget->setItem(0,0, newItem);
}

void MainWindow::on_pushButton_2_clicked()
{
    SendToServer(ui->lineEdit->text(), myNickName);
}


void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_2_clicked();
}

