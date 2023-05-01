#include "mainwindow_client.h"
#include "registrationwindow_client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    RegistrationWindow r;
    r.show();
    //w.show();
    return a.exec();
}
