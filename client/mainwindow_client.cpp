#include "mainwindow_client.h"
#include "ui_mainwindow_client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1", 8888);
}

void MainWindow::SendToServer(QString str)
{

    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint16(0) << QTime::currentTime() <<str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_5);
    if(in.status() == QDataStream::Ok)
    {
        /*
        QString str;
        in >> str;
        ui->textBrowser->append(str);
        старый прием данных
        */
        for(;;) //бесконечный цикл брух
        {
            if(nextBlockSize == 0)// размер блока не известен
            {
                if(socket->bytesAvailable() < 2)//для чтения доступно не меньше 2 байт
                {
                    break;
                }
                in >> nextBlockSize;// размер блока
            }
            if(socket->bytesAvailable() < nextBlockSize)// размер блока сравнивается с кол-вом байт от сервака
            {
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize = 0;
            ui->textBrowser->append(time.toString() + "\n" + str);
            break;
        }
    }
    else
    {
         ui->textBrowser->append("read error");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    SendToServer(ui->lineEdit->text());
}


void MainWindow::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text());
}

