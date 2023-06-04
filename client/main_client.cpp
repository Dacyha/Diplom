#include "registrationwindow_client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("Dacyha");
    QApplication::setApplicationName("Baheriamma");

        RegistrationWindow r;
        r.show();

    return a.exec();
}


