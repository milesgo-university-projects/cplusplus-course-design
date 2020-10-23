#ifndef QUESTIONDETAILWIDGET
#define QUESTIONDETAILWIDGET
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "singleansweritem.h"
#include "answer.h"
#include "questiondetailwidget.h"
#include "questiontitleanddetail.h"
#include "pagelistwidget.h"
class SingleAnswerItem;
class QuestionTitleAndDetail;
//标题最多30字，每一页放四个回答，第一页虽然有标题，但也放四个回答

class QuestionDetailWidget:public PageListWidget
{
    Q_OBJECT
    public:
        QuestionDetailWidget(const int &ddelta=5,QWidget *parent=0);
        void setModeAndInfo(const int &mode,const int &questionID,const int &answerID=0);
        void clearInfo();
        ~QuestionDetailWidget();
        QuestionTitleAndDetail *titleAndDetail;
    private:
        QVector<SingleAnswerItem *> answerItemList;
        QVector<bool> isShowing;
        virtual void setItems(int ll,int rr,int bound) override;
    private slots:
        virtual void getNextPage() override;
        virtual void getLastPage() override;
        void onSortSignalReceived(int flag);
        void onTitleAndDetailConcernStateChanged(int userID);
};

#endif // QUESTIONDETAILWIDGET

