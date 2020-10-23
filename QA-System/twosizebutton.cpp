#include "twosizebutton.h"
#include <QDebug>

//构造函数
twoSizeButton::twoSizeButton(QString smallButtonName,QString bigButtonName,QSize buttonSize,QSize smallSize,QSize bigSize,QWidget *parent):QPushButton(parent)
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(buttonSize);
    this->smallSize=smallSize;
    this->bigSize=bigSize;

    smallLabel = new QLabel(this);                  //新建
    smallLabel->setAttribute(Qt::WA_TranslucentBackground,true);
    bigLabel = new QLabel(this);
    bigLabel->setAttribute(Qt::WA_TranslucentBackground,true);
    smallLabel->setFixedSize(smallSize);                  //更改大小
    bigLabel->setFixedSize(bigSize);
    smallLabel->setAttribute(Qt::WA_TranslucentBackground);
    smallLabel->setPixmap(QPixmap("../data/images/"+smallButtonName+".png")); //加载图片
    bigLabel->setAttribute(Qt::WA_TranslucentBackground);
    bigLabel->setPixmap(QPixmap("../data/images/"+bigButtonName+".png"));
    smallLabel->move((width()-smallSize.width())/2,(height()-smallSize.height())/2);
    bigLabel->move((width()-bigSize.width())/2,(height()-bigSize.height())/2);

    smallLabel->show();                             //显示
    bigLabel->hide();
}

twoSizeButton::~twoSizeButton()
{
    delete smallLabel;
    delete bigLabel;
}

void twoSizeButton::setSmallSize(QSize size)
{
    smallSize=size;
}

void twoSizeButton::setSmallSize(int w,int h)
{
    smallSize=QSize(w,h);
}

void twoSizeButton::setBigSize(QSize size)
{
    bigSize=size;
}

void twoSizeButton::setBigSize(int w,int h)
{
    bigSize=QSize(w,h);
}

void twoSizeButton::setPicture(QString smallButtonName, QString bigButtonName)
{
    smallLabel->setPixmap(QPixmap("../data/images/"+smallButtonName+".png"));
    bigLabel->setPixmap(QPixmap("../data/images/"+bigButtonName+".png"));
}

void twoSizeButton::enterEvent(QEvent *e)
{
    smallLabel->hide();
    bigLabel->show();
    QPushButton::enterEvent(e);
}

void twoSizeButton::leaveEvent(QEvent *e)
{
    smallLabel->show();
    bigLabel->hide();
    QPushButton::leaveEvent(e);
}
