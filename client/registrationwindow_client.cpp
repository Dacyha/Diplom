#include "registrationwindow_client.h"
#include "ui_registrationwindow_client.h"

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);
    mainWindow = new MainWindow;

    connect(this, &RegistrationWindow::sendNickName, mainWindow, &MainWindow::readNickName);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_pushButton_clicked()
{
    emit sendNickName(ui->lineEdit->text());
    ui->lineEdit->clear();
    mainWindow->show();
    this->close();
}


void RegistrationWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

