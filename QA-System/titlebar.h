#ifndef TITLEBAR
#define TITLEBAR

#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QPoint>
#include <QIcon>
#include <QApplication>
#include <QDebug>
#include "twosizebutton.h"
#include "simplebutton.h"
#include "overall.h"
#include "searchedit.h"
class SearchEdit;
//标题栏
class titleBar:public QWidget
{
    Q_OBJECT
    public:
        titleBar(QWidget *parent=0);
        ~titleBar();
        twoSizeButton *lastPageButton;
    protected:
        void mouseMoveEvent(QMouseEvent *e);              //鼠标移动事件
        void mousePressEvent(QMouseEvent *e);             //鼠标点击事件
        void mouseReleaseEvent(QMouseEvent *e);           //鼠标松开
        bool eventFilter(QObject *obj, QEvent *e);
    private slots:
        void onClicked();
    private:
        QPushButton *closeButton,*minSizeButton;
        QLabel *iconLabel,*titleLabel,*closeButtonLabel,*minSizeButtonLabel;
        SearchEdit *searchEdit;
        QHBoxLayout *titleLayout;
        bool isPressed;
        QPoint point;
};

#endif // TITLEBAR

