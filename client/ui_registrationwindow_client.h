/********************************************************************************
** Form generated from reading UI file 'registrationwindow_client.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONWINDOW_CLIENT_H
#define UI_REGISTRATIONWINDOW_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistrationWindow
{
public:
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QWidget *RegistrationWindow)
    {
        if (RegistrationWindow->objectName().isEmpty())
            RegistrationWindow->setObjectName("RegistrationWindow");
        RegistrationWindow->resize(285, 104);
        pushButton = new QPushButton(RegistrationWindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(190, 40, 80, 24));
        lineEdit = new QLineEdit(RegistrationWindow);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 40, 161, 24));
        label = new QLabel(RegistrationWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 81, 16));

        retranslateUi(RegistrationWindow);

        QMetaObject::connectSlotsByName(RegistrationWindow);
    } // setupUi

    void retranslateUi(QWidget *RegistrationWindow)
    {
        RegistrationWindow->setWindowTitle(QCoreApplication::translate("RegistrationWindow", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("RegistrationWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        lineEdit->setText(QString());
        label->setText(QCoreApplication::translate("RegistrationWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\270\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistrationWindow: public Ui_RegistrationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONWINDOW_CLIENT_H
