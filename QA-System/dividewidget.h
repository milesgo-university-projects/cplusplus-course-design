#ifndef DIVIDEWIDGET
#define DIVIDEWIDGET
#include <QWidget>
#include <QPaintEvent>
#include <QPen>
#include <QPainter>
#include <QColor>

class DivideWidget:public QWidget
{
    Q_OBJECT
    public:
        DivideWidget(QWidget *parent=0);
        DivideWidget(const int &length,const int &flag=0,QWidget *parent=0);
        ~DivideWidget();
    protected:
        void paintEvent(QPaintEvent *e);
    private:
        int length,flag,thickness;
        QColor color;
    public:
        void setColor(const QColor& color);
        void setThickness(const int &thickness);
};

#endif // DIVIDEWIDGET

