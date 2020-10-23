#ifndef SIMPLEBUTTON
#define SIMPLEBUTTON
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QEvent>
#include <QPalette>

class SimpleButton:public QWidget
{//当鼠标移到上面来时，字体加粗
    Q_OBJECT
    public:
        SimpleButton(QWidget *parent=0);
        SimpleButton(const QString &pictureLocation,const QString &word,QWidget *parent=0);
        ~SimpleButton();
        void setFixed(bool flag);
        void setText(const QString &text);
    private:
        QLabel *pictureLabel,*wordLabel;
        QHBoxLayout *mainLayout;
        bool fixed;
        QFont normalFont=QFont("Microsoft YaHei",10,QFont::Normal),bigFont=QFont("Microsoft YaHei",15,QFont::Bold);
    protected:
        void enterEvent(QEvent *e);
        void leaveEvent(QEvent *e);
        void mousePressEvent(QMouseEvent *e);
    public slots:
        void click();
    signals:
        void clicked();
};

#endif // SIMPLEBUTTON

