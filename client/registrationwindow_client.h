#ifndef REGISTRATIONWINDOW_CLIENT_H
#define REGISTRATIONWINDOW_CLIENT_H

#include <QWidget>
#include "mainwindow_client.h"

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

    void saveSettings();
    void loadSettings();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::RegistrationWindow *ui;
    MainWindow *mainWindow;

    QSettings* settings;
    QString myNickName;

signals:
    void sendNickName(QString);
};

#endif // REGISTRATIONWINDOW_CLIENT_H
