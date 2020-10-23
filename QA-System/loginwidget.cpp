#include "loginwidget.h"

class Widget;

//构造函数
loginDialog::loginDialog(QWidget *parent):QDialog(parent)
{
    //setWindowIcon(QIcon("../option/titlebarImages/library.png"));
    this->resize(225,130);                                            //设置大小
    this->setWindowFlags(Qt::FramelessWindowHint);
    messageLabel = new QLabel;
    messageLabel->setText(tr("             瞎扯问答"));               //登录界面中心文字
    closeButton = new QPushButton;                              //关闭按钮
    closeButton->setText(tr("关闭"));
    closeButton->setFocusPolicy(Qt::NoFocus);
    signUpButton = new QPushButton;
    signUpButton->setText(tr("注册"));
    signUpButton->setFocusPolicy(Qt::NoFocus);
    loginButton = new QPushButton;                              //登录按钮
    loginButton->setText(tr("登录"));
    loginButton->setFocusPolicy(Qt::NoFocus);
    passwordLineEdit = new QLineEdit;                   //密码输入框
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    userLineEdit = new QLineEdit;                               //用户输入线
    passwordLabel = new QLabel;                                 //密码标签
    passwordLabel->setText(tr("密码"));
    userLabel = new QLabel;                                     //用户标签
    userLabel->setText(tr("用户名"));

    passwordLayout = new QHBoxLayout;                                 //布局
    passwordLayout->addWidget(passwordLabel,1);
    passwordLayout->addWidget(passwordLineEdit,4);
    userLayout = new QHBoxLayout;
    userLayout->addWidget(userLabel,1);
    userLayout->addWidget(userLineEdit,4);
    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(closeButton);
    buttonLayout->addWidget(signUpButton);
    buttonLayout->addWidget(loginButton);
    vLayout = new QVBoxLayout;
    vLayout->addWidget(messageLabel);
    vLayout->addLayout(userLayout);
    vLayout->addLayout(passwordLayout);
    vLayout->addLayout(buttonLayout);
    this->setLayout(vLayout);
    connect(loginButton,SIGNAL(clicked()),this,SLOT(checkPushed()));   //连接信号与槽
    connect(signUpButton,SIGNAL(clicked()),this,SLOT(onSignUpButtonPushed()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(passwordLineEdit,SIGNAL(returnPressed()),loginButton,SLOT(click()));
    userLineEdit->setFocus();
    QWidget::setTabOrder(userLineEdit,passwordLineEdit);               //设置顺序
    QWidget::setTabOrder(passwordLineEdit,loginButton);
    QWidget::setTabOrder(loginButton,signUpButton);
    QWidget::setTabOrder(signUpButton,closeButton);
}

//析构函数
loginDialog::~loginDialog()
{
    delete messageLabel;
    delete closeButton;
    delete signUpButton;
    delete loginButton;
    delete passwordLineEdit;
    delete userLineEdit;
    delete passwordLabel;
    delete userLabel;
    delete passwordLayout;
    delete userLayout;
    delete buttonLayout;
    delete vLayout;
}

//按下按钮后的回调函数
void loginDialog::checkPushed()
{
    if(User::checkUserPassword(userLineEdit->text().trimmed(),passwordLineEdit->text().trimmed()))
    {
        Overall::currentUserID=User::userNameToID[userLineEdit->text().trimmed()];
        Overall::currentLookingUserID=Overall::currentUserID;
        Overall::currentUserName=userLineEdit->text().trimmed();
        this->accept();
    }
    else
    {
        QMessageBox message(QMessageBox::Warning,"警告","用户名或密码错误！",QMessageBox::Yes,NULL);
        message.setButtonText(QMessageBox::Yes,"好的");
        message.exec();
        passwordLineEdit->clear();
        passwordLineEdit->setFocus();
    }
}

void loginDialog::onSignUpButtonPushed()
{
    this->close();
    SignUpWidget *signUpWidget = new SignUpWidget;
    signUpWidget->show();
    connect(signUpWidget,SIGNAL(rejected()),this,SLOT(show()));
    connect(signUpWidget,SIGNAL(accepted()),this,SLOT(show()));
}

void loginDialog::showEvent(QShowEvent *e)
{
    this->userLineEdit->setFocus();
    this->userLineEdit->clear();
    this->passwordLineEdit->clear();
    QDialog::showEvent(e);
}
