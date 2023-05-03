#ifndef MAINWINDOW_CLIENT_H
#define MAINWINDOW_CLIENT_H

#include <QMainWindow>
#include<QTcpSocket>
#include<QTime>
#include<QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    QString myNickName;
    void SendToServer(QString str, QString myNickName);
    void SendToServerNickName(QString myNickName);
    void EditTable( QMap<QString, QTcpSocket*> forTable);

public slots:
    void slotReadyRead();

    void readNickName(QString nick);
};
#endif // MAINWINDOW_CLIENT_H
