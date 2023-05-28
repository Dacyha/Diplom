#include "mainwindow_client.h"
#include "registrationwindow_client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("Dacyha");
    QApplication::setApplicationName("Shagging Sheep");

        RegistrationWindow r;
        r.show();
        //MainWindow m;
        //m.show();

    return a.exec();
}


