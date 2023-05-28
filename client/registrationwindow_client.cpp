#include "registrationwindow_client.h"
#include "ui_registrationwindow_client.h"

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);

    settings = new QSettings("D:/qt project/Diplom/client/settings.ini", QSettings::IniFormat,  this);
    loadSettings();
    mainWindow = new MainWindow;
    connect(this, &RegistrationWindow::sendNickName, mainWindow, &MainWindow::readNickName);
    if (myNickName != "")
    {
        ui->lineEdit->setText(myNickName);
    }
}

RegistrationWindow::~RegistrationWindow()
{
    saveSettings();
    delete ui;
}

void RegistrationWindow::saveSettings()
{
    settings->setValue("nick_name", myNickName);
}

void RegistrationWindow::loadSettings()
{
    myNickName = (settings->value("nick_name", "").toString());
}

void RegistrationWindow::on_pushButton_clicked()
{
    myNickName = ui->lineEdit->text();
    emit sendNickName(myNickName);
    ui->lineEdit->clear();
    mainWindow->show();
    this->close();
}

void RegistrationWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

