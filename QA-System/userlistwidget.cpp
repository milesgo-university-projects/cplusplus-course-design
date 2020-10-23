#include "userlistwidget.h"

UserListWidget::UserListWidget(const int &mode,const int &userID, QWidget *parent):PageListWidget(parent)
{
    if(Overall::windowControl)
    {
        int loc=Overall::windowStack.size();
        Overall::windowStack.push(mode+7);
        Overall::stackLocationToID[loc]=userID;
        Overall::stackLocationToMineOrHis[loc]=Overall::mainWindow->getGuideZoneMode();
    }
    delta=5;
    userItemList.clear();

    QSet<int> userSet;
    if(mode==0)
        userSet=Overall::mainWindow->getFansUserSet(userID);
    else if(mode==1)
        userSet=Overall::mainWindow->getConcernUserSet(userID);
    for(QSet<int>::iterator it=userSet.begin();it!=userSet.end();it++)
        infoList.push_back(*it);

    for(int i=0;i<delta;i++)
    {
        userItemList.push_back(new UserItem);
        mainLayout->addWidget(userItemList[i]);
        connect(userItemList[i],SIGNAL(concernState(int,bool)),this,SLOT(onConcernStateChanged(int,bool)));
    }

    init();
    mainLayout->addLayout(buttonLayout);
}

UserListWidget::UserListWidget(QWidget *parent):PageListWidget(parent)
{

}

void UserListWidget::setItems(int ll, int rr,int bound)
{
    for(int i=ll;i<=rr;i++)
    {
        if(i>=infoList.size())
        {
            qDebug()<<"out of range in userlistwidget.cpp setitems.function";
            exit(0);
        }
        int ID=infoList[i];
        int loc=Overall::mainWindow->userIDToListLocation[ID];
        userItemList[i-ll]->changeInfo(Overall::mainWindow->userList[loc]);
        userItemList[i-ll]->showInfo();
        if(Overall::mainWindow->getGuideZoneMode()==1&&Overall::mainWindow->userList[loc].getUserID()==Overall::currentUserID)
        {
            userItemList[i-ll]->setConcernOrNotButtonHidden(true);
            userItemList[i-ll]->setLookingDetailButtonHidden(true);
        }
        else
        {
            userItemList[i-ll]->setConcernOrNotButtonHidden(false);
            userItemList[i-ll]->setLookingDetailButtonHidden(false);
            if(Overall::mainWindow->checkISAconcerningB(Overall::currentUserID,ID))
                userItemList[i-ll]->setConcernOrNotButtonText("取消关注");
            else
                userItemList[i-ll]->setConcernOrNotButtonText("关注他");
        }
    }
    for(int i=rr+1;i<=bound;i++)
        userItemList[i-ll]->hideInfo();
}

void UserListWidget::onConcernStateChanged(int userID, bool flag)
{
    Overall::mainWindow->makeAconcernB(Overall::currentUserID,userID,flag);
}

UserListWidget::~UserListWidget()
{
    for(int i=0;i<userItemList.size();i++)
        delete userItemList[i];
    userItemList.clear();
}
