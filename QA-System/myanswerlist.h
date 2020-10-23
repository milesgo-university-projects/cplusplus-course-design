#ifndef MYANSWERLIST
#define MYANSWERLIST
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QVector>
#include "questiondetailwidget.h"
#include "pagelistwidget.h"
class QuestionDetailWidget;

class MyAnswerList:public PageListWidget
{
    Q_OBJECT
    public:
        MyAnswerList(QWidget *parent=0);
        MyAnswerList(const int &userID,QWidget *parent=0);
        ~MyAnswerList();
    private:
        QVector<QuestionDetailWidget *> answerItemList;
        virtual void setItems(int ll,int rr,int bound);
};

#endif // MYANSWERLIST

