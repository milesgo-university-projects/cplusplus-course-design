#ifndef QUESTIONHEADLINELIST
#define QUESTIONHEADLINELIST
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QScrollArea>
#include "questiontitleanddetail.h"
#include "pagelistwidget.h"
#include "question.h"

class Question;

class QuestionHeadLineList:public PageListWidget
{
    Q_OBJECT
    public:
        QuestionHeadLineList(const int &mode=0,const int &userID=0,QWidget *parent=0);//mode=0表示全部提问//mode=1表示关注的提问//mode=2表示我的提问//mode=3表示按内容搜索,mode=4表示按时间搜索
        QuestionHeadLineList(const QString &content,QWidget *parent=0);
        QuestionHeadLineList(const QDateTime &startDateTime,const QDateTime &endDateTime,QWidget *parent=0);
        ~QuestionHeadLineList();
    private:
        int mode;
        QVector<QuestionTitleAndDetail *> questionItemList;
        QVector<bool> isShowing;
        virtual void setItems(int ll,int rr,int bound) override;
    private slots:
        void onConcernStateChange(int userID);
};

#endif // QUESTIONHEADLINELIST

