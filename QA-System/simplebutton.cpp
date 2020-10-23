#include "simplebutton.h"

SimpleButton::SimpleButton(QWidget *parent):QWidget(parent)
{
    pictureLabel=NULL;
    wordLabel=NULL;
    mainLayout=NULL;
}

SimpleButton::SimpleButton(const QString &pictureLocation, const QString &word, QWidget *parent):QWidget(parent)
{
    setFixedSize(150,40);
    pictureLabel = new QLabel;
    wordLabel = new QLabel;
    //加载图片，设置字体，默认字体浅
    if(pictureLocation!="")
    {

    }
    wordLabel->setText(word);
    wordLabel->setFont(normalFont);

    mainLayout = new QHBoxLayout;

    mainLayout->addWidget(wordLabel,2);
    mainLayout->addWidget(pictureLabel,1);
    setLayout(mainLayout);
}

SimpleButton::~SimpleButton()
{
    if(pictureLabel!=NULL)
    {
        delete pictureLabel;
        pictureLabel=NULL;
    }
    if(wordLabel!=NULL)
    {
        delete wordLabel;
        wordLabel=NULL;
    }
    if(mainLayout!=NULL)
    {
        delete mainLayout;
        mainLayout=NULL;
    }
}

void SimpleButton::enterEvent(QEvent *e)
{
    wordLabel->setFont(bigFont);
    QWidget::enterEvent(e);
}

void SimpleButton::leaveEvent(QEvent *e)
{
    if(!fixed)
        wordLabel->setFont(normalFont);
    QWidget::leaveEvent(e);
}

void SimpleButton::mousePressEvent(QMouseEvent *e)
{
    emit clicked();
    QWidget::mousePressEvent(e);
}

void SimpleButton::setFixed(bool flag)
{
    this->fixed=flag;
    if(!flag)
        wordLabel->setFont(normalFont);
    else
        wordLabel->setFont(bigFont);
}

void SimpleButton::click()
{
    emit clicked();
}

void SimpleButton::setText(const QString &text)
{
    wordLabel->setText(text);
}
