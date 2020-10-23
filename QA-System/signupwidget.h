#ifndef SIGNUPWIDGET
#define SIGNUPWIDGET
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QWidget>
#include <QRegExp>
#include <QValidator>
#include <QDebug>
#include "overall.h"
#include "user.h"

class SignUpWidget:public QDialog
{
    Q_OBJECT
    public:
        SignUpWidget(QWidget *parent=0);
        ~SignUpWidget();
    private:
        QPushButton *signUpButton,*cancelButton;
        QLineEdit *userNameEdit,*passwordEdit,*passwordAgainEdit;
        QLabel *userNameLabel,*passwordLabel,*passwordAgainLabel;
        QHBoxLayout *buttonLayout,*userNameLayout,*passwordLayout,*passwordAgainLayout;
        QVBoxLayout *mainLayout;
    private slots:
        void onSignUpButtonClicked();
        void onCancelButtonClicked();
};


#endif // SIGNUPWIDGET

