#include "mainwindow_client.h"
#include "ui_mainwindow_client.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString settingsDir = "C:/Users/" + QDir::home().dirName() + "/Documents/" + QApplication::applicationName() + "/settings.ini";
    settings = new QSettings(settingsDir, QSettings::IniFormat,  this);
    loadSettings();

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    socket->connectToHost("127.0.0.1", 8888);

    FormSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveSettings()
{
    settings->setValue("geometry", geometry());
}

void MainWindow::loadSettings()
{
     setGeometry(settings->value("geometry", QRect(800, 400, 400, 300)).toRect());
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
         //ui->textBrowser->append("read error");// убрать
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
    setWindowTitle(myNickName);
    SendToServerNickName(myNickName);
}

void MainWindow::on_pushButton_2_clicked()
{
    SendToServer(ui->lineEdit->text(), myNickName);
}


void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_2_clicked();
}

void MainWindow::closeEvent(QCloseEvent*)
{
    saveSettings();
    socket->disconnectFromHost();
}

void MainWindow::FormSettings()
{
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString nickNameClient = ui->tableWidget->item(row,column)->text();//заготовочка
     ui->textBrowser->append(nickNameClient);
}

