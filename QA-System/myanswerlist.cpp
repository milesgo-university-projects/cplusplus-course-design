#include "myanswerlist.h"

MyAnswerList::MyAnswerList(QWidget *parent):PageListWidget(parent)
{

}

MyAnswerList::MyAnswerList(const int &userID,QWidget *parent):PageListWidget(parent)
{
    if(Overall::windowControl)
    {
        int loc=Overall::windowStack.size();
        Overall::windowStack.push(9);
        Overall::stackLocationToID[loc]=userID;
        Overall::stackLocationToMineOrHis[loc]=Overall::mainWindow->getGuideZoneMode();
    }
    delta=2;
    for(int i=0;i<delta;i++)
    {
        answerItemList.push_back(new QuestionDetailWidget(1));
        connect(answerItemList[i]->titleAndDetail,SIGNAL(showQuestionSignal(int)),Overall::mainWindow,SLOT(ShowQuestion(int)));
        mainLayout->addWidget(answerItemList[i]);
    }
    mainLayout->addLayout(buttonLayout);

    QSet<int> answerSet=Overall::mainWindow->getMyAnswerSet(userID);
    for(QSet<int>::iterator it=answerSet.begin();it!=answerSet.end();it++)
    {
        infoList.push_back(*it);
    }
    qSort(infoList.begin(),infoList.end(),Function::compareAnswerAccordingToDateTime);//按照时间排序
    init();
}

void MyAnswerList::setItems(int ll, int rr, int bound)
{
    for(int i=ll;i<=rr;i++)
    {
        if(i>=infoList.size())
        {
            qDebug()<<"out of range in myanswerlist.cpp setitems.function";
            exit(0);
        }
        answerItemList[i-ll]->setModeAndInfo(1,Answer::answerIDToQuestionID[infoList[i]],infoList[i]);
    }
    for(int i=rr+1;i<=bound;i++)
        answerItemList[i-ll]->clearInfo();
}

MyAnswerList::~MyAnswerList()
{
    for(int i=0;i<answerItemList.size();i++)
        delete answerItemList[i];
    answerItemList.clear();
}
