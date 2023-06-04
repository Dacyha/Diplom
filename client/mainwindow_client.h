#ifndef MAINWINDOW_CLIENT_H
#define MAINWINDOW_CLIENT_H

#include <QMainWindow>
#include<QTcpSocket>
#include<QTime>
#include<QMap>
#include<QSettings>
#include<QList>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void saveSettings();
    void loadSettings();

private slots:
    void on_pushButton_2_clicked();

    void on_lineEdit_returnPressed();

    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    QString myNickName;
    QSettings* settings;
    void SendToServer(QString str, QString myNickName);
    void SendToServerNickName(QString myNickName);
    void closeEvent(QCloseEvent *event);
    void FormSettings();

public slots:
    void slotReadyRead();

    void readNickName(QString nick);
};
#endif // MAINWINDOW_CLIENT_H
