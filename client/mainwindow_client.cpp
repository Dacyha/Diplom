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
    socket->connectToHost("127.0.0.1", 8888);
}

MainWindow::~MainWindow()
{
    //socket->close();
    delete ui;
}

void MainWindow::SendToServer(QString str, QString myNickName)
{
    QString sendCode = "2";
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << sendCode << QTime::currentTime() << myNickName << str;
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::SendToServerNickName(QString myNickName)
{
    QString sendCode = "1";
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << sendCode  << myNickName;
    socket->write(Data);
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_5);
    if(in.status() == QDataStream::Ok)
    {
        QString str;
        QTime time;
        QString nickNameClient;
        QString readCode;
         in >>  readCode;
         switch (readCode.toInt()) {
            case 1:
                ui->textBrowser->append("code 1");//заменить

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

void MainWindow::readNickName(QString nick)
{
    myNickName=nick;
    SendToServerNickName(myNickName);
    QMap<QString, QTcpSocket*> forTable;
    forTable.insert(myNickName, socket);
    EditTable(forTable);
}

void MainWindow::EditTable(QMap<QString, QTcpSocket*> forTable)
{
    QTableWidgetItem *newItem = new QTableWidgetItem();
    //QString oleg = forTable.key(socket);
    newItem->setText(forTable.key(socket));
    ui->tableWidget->setItem(0,0, newItem);
}

void MainWindow::on_pushButton_2_clicked()
{
    SendToServer(ui->lineEdit->text(), myNickName);
}


void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_2_clicked();
}

