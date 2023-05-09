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

    ui->tableWidget->verticalHeader()->hide();// перенести в подобающее место(туда где буду настраивать размер элементов)
    ui->tableWidget->horizontalHeader()->hide();// перенести в подобающее место
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
    if(out.status() == QDataStream::Ok && str != "")
    {
        out << sendCode << QTime::currentTime() << myNickName << str;
        socket->write(Data);
        ui->lineEdit->clear();
    }
    else
    {
         ui->textBrowser->append("read error");// убрать
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
        qint64 it;
        QList<QString> clientTable;
         in >>  readCode;
         switch (readCode.toInt()) {
            case 1:
             in >> clientTable;
             ui->tableWidget->setRowCount(clientTable.size());
             it = 0;
             foreach(QString nickNameClient, clientTable )
             {
                 QTableWidgetItem *newItem = new QTableWidgetItem();
                 newItem->setText(nickNameClient);
                 ui->tableWidget->setItem(0,it, newItem);
                 it++;
             }
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


void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString nickNameClient = ui->tableWidget->item(row,column)->text();//заготовочка
     ui->textBrowser->append(nickNameClient);
}

