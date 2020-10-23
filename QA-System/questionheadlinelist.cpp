#include "questionheadlinelist.h"

QuestionHeadLineList::QuestionHeadLineList(const int &mode,const int &userID,QWidget *parent):PageListWidget(parent)
{
    this->mode=mode;
    if(Overall::windowControl)
    {
        int loc=Overall::windowStack.size();
        Overall::windowStack.push(mode+4);
        Overall::stackLocationToID[loc]=userID;
        Overall::stackLocationToMineOrHis[loc]=Overall::mainWindow->getGuideZoneMode();
    }
    delta=4;
    for(int i=0;i<delta;i++)
    {
        questionItemList.push_back(new QuestionTitleAndDetail);
        isShowing.push_back(true);
        questionItemList[i]->setMode(1);
        connect(questionItemList[i],SIGNAL(showQuestionSignal(int)),Overall::mainWindow,SLOT(ShowQuestion(int)));
        connect(questionItemList[i],SIGNAL(concernStateChanged(int)),this,SLOT(onConcernStateChange(int)));
        mainLayout->addWidget(questionItemList[i]);
    }
    mainLayout->addLayout(buttonLayout);

    if(mode==0)
    {
        QMap<int,int> mp=Question::questionIDToUserID;
        for(QMap<int,int>::iterator it=mp.begin();it!=mp.end();it++)
        {
            infoList.push_back(it.key());
        }
    }
    else if(mode==1)
    {
        QSet<int> concernedQuestionSet=Overall::mainWindow->getConcernedQuestionSet(userID);
        for(QSet<int>::iterator it=concernedQuestionSet.begin();it!=concernedQuestionSet.end();it++)
        {
            infoList.push_back(*it);
        }
    }
    else if(mode==2)
    {
        QSet<int> questionSet=Overall::mainWindow->getQuestionSet(userID);
        for(QSet<int>::iterator it=questionSet.begin();it!=questionSet.end();it++)
        {
            infoList.push_back(*it);
        }
    }
    qSort(infoList.begin(),infoList.end(),Function::compareQuestionAccordingToDateTime);
    init();
}

QuestionHeadLineList::QuestionHeadLineList(const QString &content, QWidget *parent):PageListWidget(parent)
{//线性遍历所有的提问，根据内容筛选，筛选后根据时间排序
    mode=3;
    if(Overall::windowControl)
    {
        Overall::windowStack.push(12);
        Overall::contentStack.push(content);
    }
    delta=4;
    for(int i=0;i<delta;i++)
    {
        questionItemList.push_back(new QuestionTitleAndDetail);
        isShowing.push_back(true);
        questionItemList[i]->setMode(1);
        connect(questionItemList[i],SIGNAL(showQuestionSignal(int)),Overall::mainWindow,SLOT(ShowQuestion(int)));
        connect(questionItemList[i],SIGNAL(concernStateChanged(int)),this,SLOT(onConcernStateChange(int)));
        mainLayout->addWidget(questionItemList[i]);
    }
    mainLayout->addLayout(buttonLayout);
    QMap<int,class Question>::iterator endIterator =Overall::mainWindow->questionIDToQuestionObject.end();
    for(QMap<int,class Question>::Iterator it=Overall::mainWindow->questionIDToQuestionObject.begin();it!=endIterator;it++)
    {
        class Question tmpQuestion=it.value();
        if(tmpQuestion.getTitle().contains(content))
        {
            infoList.push_back(it.key());
        }
    }
    qSort(infoList.begin(),infoList.end(),Function::compareQuestionAccordingToDateTime);
    init();
}

QuestionHeadLineList::QuestionHeadLineList(const QDateTime &startDateTime, const QDateTime &endDateTime, QWidget *parent):PageListWidget(parent)
{//线性遍历所有的提问，根据时间筛选，筛选后根据时间排序
    mode=4;
    if(Overall::windowControl)
    {
        Overall::windowStack.push(13);
        Overall::startDateTimeStack.push(startDateTime);
        Overall::endDateTimeStack.push(endDateTime);
    }
    delta=4;
    for(int i=0;i<delta;i++)
    {
        questionItemList.push_back(new QuestionTitleAndDetail);
        isShowing.push_back(true);
        questionItemList[i]->setMode(1);
        connect(questionItemList[i],SIGNAL(showQuestionSignal(int)),Overall::mainWindow,SLOT(ShowQuestion(int)));
        mainLayout->addWidget(questionItemList[i]);
    }
    mainLayout->addLayout(buttonLayout);
    QMap<int,class Question>::iterator endIterator =Overall::mainWindow->questionIDToQuestionObject.end();
    for(QMap<int,class Question>::Iterator it=Overall::mainWindow->questionIDToQuestionObject.begin();it!=endIterator;it++)
    {
        class Question tmpQuestion=it.value();
        QDateTime dateTime=tmpQuestion.getDateTime();
        if(dateTime>=startDateTime&&dateTime<=endDateTime)
        {
            infoList.push_back(it.key());
        }
    }
    qSort(infoList.begin(),infoList.end(),Function::compareQuestionAccordingToDateTime);
    init();
}

void QuestionHeadLineList::setItems(int ll, int rr, int bound)
{
    try
    {
        for(int i=ll;i<=rr;i++)
        {
            if(i>=infoList.size())
            {
                throw QString("out of range in questionheadlist.cpp setItems.function");
                break;
            }
            class Question tmpQuestion=Overall::mainWindow->questionIDToQuestionObject[infoList.at(i)];
            questionItemList[i-ll]->setInfo(tmpQuestion.getTitle(),tmpQuestion.getContent(),tmpQuestion.getDateTime(),Overall::mainWindow->getUserName(tmpQuestion.getUserID()),tmpQuestion.getAnswerSet().size(),tmpQuestion.getUserID(),tmpQuestion.getInfoID());
            isShowing[i-ll]=true;
        }
        for(int i=rr+1;i<=bound;i++)
        {
            questionItemList[i-ll]->clearInfo();
            isShowing[i-ll]=false;
        }
    }
    catch(QString &error)
    {
        qDebug()<<error;
        exit(0);
    }
}

void QuestionHeadLineList::onConcernStateChange(int userID)
{
    for(int i=0;i<delta;i++)
    {
        if(!isShowing[i])
            break;
        int checkingUserID=questionItemList[i]->getUserID();
        if(checkingUserID==userID)
        {
            questionItemList[i]->updateConcernOrNotButton();
        }
    }
}

QuestionHeadLineList::~QuestionHeadLineList()
{
    for(int i=0;i<questionItemList.size();i++)
        delete questionItemList[i];
    questionItemList.clear();
}
