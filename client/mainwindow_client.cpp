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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1", 8888);
}

void MainWindow::SendToServer(QString str, QString nickNameTest)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << QTime::currentTime() << nickNameTest << str;
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_5);
    if(in.status() == QDataStream::Ok)
    {
        QString str;
        QTime time;
        QString nickNameTest1;
        in >> time >> nickNameTest1 >> str;
        if (nickNameTest1 == nickNameTest){
            ui->textBrowser->append(time.toString() + "\n" + "Я: "+ str+ "\n");
            }
        else if (nickNameTest1 != nickNameTest){
            ui->textBrowser->append(time.toString() + "\n" + nickNameTest1 +": "+ str+ "\n");
        }


    }
    else
    {
         ui->textBrowser->append("read error");
    }
}

void MainWindow::readNickName(QString nick)
{
    nickNameTest=nick;
}

void MainWindow::on_pushButton_2_clicked()
{
    SendToServer(ui->lineEdit->text(), nickNameTest);
}


void MainWindow::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text(), nickNameTest);
}

