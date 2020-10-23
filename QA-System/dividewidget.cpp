#include "dividewidget.h"

DivideWidget::DivideWidget(QWidget *parent):QWidget(parent)
{
    color=QColor(139,139,139);
    thickness=10;
}

DivideWidget::DivideWidget(const int &length, const int &flag,QWidget *parent):QWidget(parent)
{
    this->length=length;
    this->flag=flag;
    color=QColor(139,139,139);
    thickness=10;
}

DivideWidget::~DivideWidget()
{

}

void DivideWidget::setColor(const QColor &color)
{
    this->color=color;
}

void DivideWidget::setThickness(const int &thickness)
{
    this->thickness=thickness;
}

void DivideWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(color);
    if(flag==0)
        painter.drawLine(5,this->height()/2,length,this->height()/2);
    else
        painter.drawLine(this->width()/2,5,this->width()/2,length);
    QWidget::paintEvent(e);
}
