#include "questiondetailwidget.h"

QuestionDetailWidget::QuestionDetailWidget(const int &ddelta,QWidget *parent):PageListWidget(parent)
{
    delta=ddelta;
    titleAndDetail = new QuestionTitleAndDetail;

    mainLayout->addWidget(titleAndDetail);
    for(int i=0;i<delta;i++)
    {
        answerItemList.push_back(new SingleAnswerItem);
        isShowing.push_back(true);
        mainLayout->addWidget(answerItemList[i]);
        answerItemList[i]->setStyleSheet("border-width: 1px");
        answerItemList[i]->setStyleSheet("background-color: rgb(111,111,111)");
        connect(answerItemList[i],SIGNAL(concernStateChanged(int)),titleAndDetail,SLOT(updateConcernOrNotButton()));
    }
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void QuestionDetailWidget::setModeAndInfo(const int &mode, const int &questionID, const int &answerID)
{
    if(mode==0)
    {//提问详情列表
        if(Overall::windowControl)
        {
            int loc=Overall::windowStack.size();
            Overall::windowStack.push(3);
            Overall::stackLocationToID[loc]=questionID;
            Overall::stackLocationToMineOrHis[loc]=Overall::mainWindow->getGuideZoneMode();
        }
        if(!Overall::mainWindow->questionIDToQuestionObject.contains(questionID))
        {
            qDebug()<<"no such question number"<<questionID;
            return;
        }
        class Question tmpQuestion=Overall::mainWindow->questionIDToQuestionObject[questionID];
        infoList.clear();
        QSet<int> answerSet=tmpQuestion.getAnswerSet();//放在set里对于分页来说不太好控制，所以转到了Vector中
        for(QSet<int>::iterator it=answerSet.begin();it!=answerSet.end();it++)
        {
            infoList.push_back(*it);
        }
        qSort(infoList.begin(),infoList.end(),Function::compareAnswerAccordingToDateTime);//按照时间排序
        titleAndDetail->setInfo(tmpQuestion.getTitle(),tmpQuestion.getContent(),tmpQuestion.getDateTime(),Overall::mainWindow->getUserName(tmpQuestion.getUserID()),infoList.size(),tmpQuestion.getUserID(),tmpQuestion.getInfoID());
        titleAndDetail->setMode(0);

        init();
        connect(titleAndDetail,SIGNAL(sortSignal(int)),this,SLOT(onSortSignalReceived(int)));
        connect(titleAndDetail,SIGNAL(concernStateChanged(int)),this,SLOT(onTitleAndDetailConcernStateChanged(int)));
    }
    else if(mode==1)
    {//我的回答列表
        class Question tmpQuestion=Overall::mainWindow->questionIDToQuestionObject[questionID];
        infoList.clear();
        infoList.push_back(answerID);
        titleAndDetail->setInfo(tmpQuestion.getTitle(),tmpQuestion.getContent(),tmpQuestion.getDateTime(),Overall::mainWindow->getUserName(tmpQuestion.getUserID()),infoList.size(),tmpQuestion.getUserID(),tmpQuestion.getInfoID());
        titleAndDetail->setMode(1);
        setItems(0,0,0);
        nextPageButton->setHidden(true);
        lastPageButton->setHidden(true);
        totalPageLabel->setHidden(true);
        pageNumberBox->setHidden(true);
        goButton->setHidden(true);
    }
}

void QuestionDetailWidget::setItems(int ll, int rr, int bound)
{
    for(int i=ll;i<=rr;i++)
    {
        if(i>=infoList.size())
        {
            qDebug()<<"questiondetailwidget.cpp setitems.function";
            exit(0);
        }
        answerItemList[i-ll]->setAnswer(infoList[i]);
        isShowing[i-ll]=true;
    }
    for(int i=rr+1;i<=bound;i++)
    {
        answerItemList[i-ll]->clearInfo();
        isShowing[i-ll]=false;
    }
}

void QuestionDetailWidget::getLastPage()
{
    curLow-=delta;
    if(curLow<0)
    {
        curLow+=delta;
        return;
    }
    curHigh-=delta;
    if(curLow==0)
    {
        titleAndDetail->setHidden(false);
    }
    setItems(curLow,curHigh,curHigh);
}

void QuestionDetailWidget::getNextPage()
{
    curLow+=delta;
    if(curLow>=infoList.size())
    {
        curLow-=delta;
        return;
    }
    curHigh+=delta;
    titleAndDetail->setHidden(true);
    int curBound=qMin(curHigh,infoList.size()-1);
    setItems(curLow,curBound,curHigh);
}

void QuestionDetailWidget::clearInfo()
{
    titleAndDetail->clearInfo();
    answerItemList[0]->clearInfo();
    nextPageButton->setHidden(true);
    lastPageButton->setHidden(true);
    totalPageLabel->setHidden(true);
    pageNumberBox->setHidden(true);
    goButton->setHidden(true);
}

void QuestionDetailWidget::onSortSignalReceived(int flag)
{
    if(flag==0)
    {
        qSort(infoList.begin(),infoList.end(),Function::compareAnswerAccordingToDateTime);
    }
    else if(flag==1)
    {
        qSort(infoList.begin(),infoList.end(),Function::compareAnswerAccordingToPraiseNum);
    }
    curLow=0,curHigh=delta-1;
    int curBound=qMin(curHigh,infoList.size()-1);
    setItems(curLow,curBound,curHigh);
}

void QuestionDetailWidget::onTitleAndDetailConcernStateChanged(int userID)
{
    for(int i=0;i<delta;i++)
    {
        if(!isShowing[i])
            break;
        int checkingUserID=answerItemList[i]->getUserID();
        if(checkingUserID==userID)
            answerItemList[i]->updateConcernUserButton();
    }
}

QuestionDetailWidget::~QuestionDetailWidget()
{
    delete titleAndDetail;
    for(int i=0;i<answerItemList.size();i++)
        delete answerItemList[i];
}
