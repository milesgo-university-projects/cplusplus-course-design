#ifndef LOGINWIDGET
#define LOGINWIDGET
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
#include <QShowEvent>
#include "functions.h"
#include "overall.h"
#include "signupwidget.h"
#include <QDebug>

class loginDialog:public QDialog//登录界面
{
    Q_OBJECT
    public:
        loginDialog(QWidget *parent=0);
        ~loginDialog();
    private:
        QPushButton *closeButton,*loginButton,*signUpButton;
        QLineEdit *passwordLineEdit,*userLineEdit;
        QLabel *messageLabel,*passwordLabel,*userLabel;
        QHBoxLayout *passwordLayout,*userLayout,*buttonLayout;
        QVBoxLayout *vLayout;
        bool checkLoginInfo(const QString& user,const QString& password);
        void showEvent(QShowEvent *e);
    private slots:
        void checkPushed();
        void onSignUpButtonPushed();
};
#endif // LOGINWIDGET

