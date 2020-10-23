#include "signupwidget.h"

SignUpWidget::SignUpWidget(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle("用户注册");
    this->setAttribute(Qt::WA_DeleteOnClose);//窗口关闭时自动delete
    this->resize(500,200);
    signUpButton = new QPushButton;
    signUpButton->setText("注册");
    signUpButton->setFocusPolicy(Qt::NoFocus);
    cancelButton = new QPushButton;
    cancelButton->setText("取消");
    cancelButton->setFocusPolicy(Qt::NoFocus);
    userNameEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordAgainEdit = new QLineEdit;
    passwordAgainEdit->setEchoMode(QLineEdit::Password);
    userNameLabel = new QLabel;
    userNameLabel->setText("*用户名（字母、数字）     ");
    passwordLabel = new QLabel;
    passwordLabel->setText("*密码 (字母、数字，6-18位)");
    passwordAgainLabel = new QLabel;
    passwordAgainLabel->setText("*密码确认                 ");

    userNameLayout = new QHBoxLayout;
    userNameLayout->addWidget(userNameLabel);
    userNameLayout->addWidget(userNameEdit);

    passwordLayout = new QHBoxLayout;
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);

    passwordAgainLayout = new QHBoxLayout;
    passwordAgainLayout->addWidget(passwordAgainLabel);
    passwordAgainLayout->addWidget(passwordAgainEdit);

    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(signUpButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(userNameLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addLayout(passwordAgainLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(signUpButton,SIGNAL(clicked()),this,SLOT(onSignUpButtonClicked()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(onCancelButtonClicked()));
}

SignUpWidget::~SignUpWidget()
{
    delete userNameEdit;
    delete passwordEdit;
    delete passwordAgainEdit;
    delete userNameLabel;
    delete passwordLabel;
    delete passwordAgainLabel;
    delete userNameLayout;
    delete passwordLayout;
    delete passwordAgainLayout;
    delete signUpButton;
    delete cancelButton;
    delete buttonLayout;
    delete mainLayout;
}

void SignUpWidget::onSignUpButtonClicked()
{
    QString str;
    str=userNameEdit->text().trimmed();
    if(str=="")
    {
        userNameEdit->setFocus();
        QMessageBox message(QMessageBox::Warning,"警告","用户名不能为空！",QMessageBox::Yes,NULL);
        message.setButtonText(QMessageBox::Yes,"好的");
        message.exec();
        return;
    }
    if(User::userNameToID.contains(str))
    {
        QMessageBox message(QMessageBox::Warning,"警告","该用户名已被注册",QMessageBox::Yes,NULL);
        message.setButtonText(QMessageBox::Yes,"好的");
        message.exec();
        userNameEdit->clear();
        userNameEdit->setFocus();
        return;
    }
    str=passwordEdit->text().trimmed();
    QRegExp reg("^[a-zA-Z0-9]{6,18}$");//控制密码为字母和数字，且位数为6-18位
    QRegExpValidator validator(reg,0);
    int pos=0;
    if(QValidator::Acceptable!=validator.validate(str,pos))
    {
        QMessageBox message(QMessageBox::Warning,"警告","密码不符合要求，请重新输入",QMessageBox::Yes,NULL);
        message.setButtonText(QMessageBox::Yes,"好的");
        message.exec();
        passwordEdit->clear();
        passwordEdit->setFocus();
        return;
    }
    QString strAgain=passwordAgainEdit->text().trimmed();
    if(str!=strAgain)
    {
        QMessageBox message(QMessageBox::Warning,"警告","密码确认错误，请重新输入",QMessageBox::Yes,NULL);
        message.setButtonText(QMessageBox::Yes,"好的");
        message.exec();
        passwordAgainEdit->clear();
        passwordAgainEdit->setFocus();
        return;
    }
    User::userNameToID.insert(userNameEdit->text().trimmed(),Overall::userIDCnt);
    User::userIDToPassword.insert(Overall::userIDCnt++,Function::md5(passwordEdit->text().trimmed()));
    Overall::settings->setValue("userIDCnt",Overall::userIDCnt);
    QMessageBox message(QMessageBox::Information,"恭喜","注册成功",QMessageBox::Yes,NULL);
    message.setButtonText(QMessageBox::Yes,"好的");
    message.exec();
    this->accept();
}

void SignUpWidget::onCancelButtonClicked()
{
    this->reject();
}
