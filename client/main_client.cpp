//#include "mainwindow_client.h"
#include "registrationwindow_client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegistrationWindow r;
    r.show();
    return a.exec();
}
