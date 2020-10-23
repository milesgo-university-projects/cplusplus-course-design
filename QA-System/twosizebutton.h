#ifndef TWOSIZEBUTTON
#define TWOSIZEBUTTON
#include <QPushButton>
#include <QSize>
#include <QPixmap>
#include <QLabel>
#include <QEvent>

class twoSizeButton:public QPushButton
{//按钮的大小其实是固定的，改变大小的是其上面的label的大小，或者图片的大小
    Q_OBJECT
public:
    twoSizeButton(QString smallButtonName="",QString bigButtonName="",QSize buttonSize=QSize(30,30),QSize smallSize=QSize(16,16),QSize bigSize=QSize(24,24),QWidget *parent=0);
    ~twoSizeButton();
    QSize smallSize,bigSize;
    QLabel *smallLabel,*bigLabel;
    void setSmallSize(QSize size);
    void setSmallSize(int w,int h);
    void setBigSize(QSize size);
    void setBigSize(int w,int h);
    void setPicture(QString smallButtonName,QString bigButtonName);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
};

#endif // TWOSIZEBUTTON
