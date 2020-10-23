#include "useritem.h"

UserItem::UserItem(QWidget *parent):QFrame(parent)
{
    //this->setStyleSheet(".UserItem{border-width: 1px}");
    this->setStyleSheet("border: 1px solid gray");
    avatarLabel = new QLabel;
    avatarLabel->setStyleSheet("border-width: 0px");
    userNameLabel = new QLabel;
    userNameLabel->setStyleSheet("border-width: 0px");
    statisticLabel = new QLabel;
    statisticLabel->setStyleSheet("border-width: 0px");

    infoLayout = new QVBoxLayout;
    infoLayout->addWidget(userNameLabel);
    infoLayout->addWidget(statisticLabel);

    concernOrNotButton = new QPushButton;
    concernOrNotButton->setFocusPolicy(Qt::NoFocus);
    lookingDetailButton = new QPushButton;
    lookingDetailButton->setFocusPolicy(Qt::NoFocus);
    lookingDetailButton->setText("查看详细信息");

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(avatarLabel,1);
    mainLayout->addLayout(infoLayout,5);
    mainLayout->addWidget(concernOrNotButton,1);
    mainLayout->addWidget(lookingDetailButton,1);

    setLayout(mainLayout);
    connect(concernOrNotButton,SIGNAL(clicked()),this,SLOT(onConcernOrNotButtonClicked()));
    connect(lookingDetailButton,SIGNAL(clicked()),this,SLOT(onLookingDetailButtonClicked()));
}

UserItem::UserItem(class User tmpUser, QWidget *parent):QFrame(parent)
{
    userID=tmpUser.getUserID();
    avatarLabel = new QLabel;
    avatarLabel->setStyleSheet("border-width: 0px");
    userNameLabel = new QLabel;
    userNameLabel->setStyleSheet("border-width: 0px");
    statisticLabel = new QLabel;
    statisticLabel->setStyleSheet("border-width: 0px");

    QString path="../data/user/avatar/"+QString("%1").arg(tmpUser.getUserID())+".png";
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
        path="../data/user/avatar/default.png";
    else
        file.close();
    avatarLabel->setPixmap(QPixmap(path));

    userNameLabel->setText(User::IDToUserName[tmpUser.getUserID()]);

    QString info=QString("回答:%1·提问:%2·关注:%3·粉丝:%4·获赞:%5").arg(tmpUser.getMyAnswersSize()).arg(tmpUser.getMyQuestionsSize()).arg(tmpUser.getconcernUsersSize()).arg(tmpUser.getFansSize()).arg(tmpUser.getPraiseNum());
    //QString info=QString("回答:%1·提问:%2·关注:%3·粉丝:%4").arg(tmpUser.getMyAnswersSize()).arg(tmpUser.getMyQuestionsSize()).arg(tmpUser.getconcernUsersSize()).arg(tmpUser.getFansSize());
    statisticLabel->setText(info);

    infoLayout = new QVBoxLayout;
    infoLayout->addWidget(userNameLabel);
    infoLayout->addWidget(statisticLabel);

    concernOrNotButton = new QPushButton;
    concernOrNotButton->setFocusPolicy(Qt::NoFocus);
    lookingDetailButton = new QPushButton;
    lookingDetailButton->setFocusPolicy(Qt::NoFocus);
    lookingDetailButton->setText("查看详细信息");

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(avatarLabel,2);
    mainLayout->addWidget(statisticLabel,6);
    mainLayout->addWidget(concernOrNotButton,1);
    mainLayout->addWidget(lookingDetailButton,1);

    setLayout(mainLayout);
    connect(concernOrNotButton,SIGNAL(clicked()),this,SLOT(onConcernOrNotButtonClicked()));
    connect(lookingDetailButton,SIGNAL(clicked()),this,SLOT(onLookingDetailButtonClicked()));
}

void UserItem::changeInfo(class User tmpUser)
{
    userID=tmpUser.getUserID();
    QString path="../data/user/avatar/"+QString("%1").arg(tmpUser.getUserID())+".png";
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
        path="../data/user/avatar/default.png";
    else
        file.close();

    if(Overall::mainWindow->getGuideZoneMode()==1&&userID==Overall::currentUserID)
    {
        concernOrNotButton->setHidden(true);
        lookingDetailButton->setHidden(true);
    }
    else
    {
        concernOrNotButton->setHidden(false);
        lookingDetailButton->setHidden(false);
    }

    avatarLabel->setPixmap(QPixmap(path));

    userNameLabel->setText(User::IDToUserName[tmpUser.getUserID()]);

    QString info=QString("回答:%1·提问:%2·关注:%3·粉丝:%4·获赞:%5").arg(tmpUser.getMyAnswersSize()).arg(tmpUser.getMyQuestionsSize()).arg(tmpUser.getconcernUsersSize()).arg(tmpUser.getFansSize()).arg(tmpUser.getPraiseNum());
    //QString info=QString("回答:%1·提问:%2·关注:%3·粉丝:%4").arg(tmpUser.getMyAnswersSize()).arg(tmpUser.getMyQuestionsSize()).arg(tmpUser.getconcernUsersSize()).arg(tmpUser.getFansSize());
    statisticLabel->setText(info);
}

void UserItem::hideInfo()
{
    avatarLabel->setHidden(true);
    userNameLabel->setHidden(true);
    statisticLabel->setHidden(true);
    concernOrNotButton->setHidden(true);
    lookingDetailButton->setHidden(true);
}

void UserItem::showInfo()
{
    avatarLabel->setHidden(false);
    userNameLabel->setHidden(false);
    statisticLabel->setHidden(false);
    concernOrNotButton->setHidden(false);
    lookingDetailButton->setHidden(false);
}

void UserItem::onConcernOrNotButtonClicked()
{
    if(concernOrNotButton->text()=="取消关注")
    {
        concernOrNotButton->setText("关注他");
        emit concernState(userID,false);
    }
    else if(concernOrNotButton->text()=="关注他")
    {
        concernOrNotButton->setText("取消关注");
        emit concernState(userID,true);
    }
}

void UserItem::onLookingDetailButtonClicked()
{
    Overall::currentLookingUserID=userID;
    Overall::mainWindow->setGuideZoneMode(1);//设为查看它人信息的模式
    Overall::mainWindow->onEditPersonalInformationButtonClicked();
}

void UserItem::setConcernOrNotButtonText(QString info)
{
    concernOrNotButton->setText(info);
}

void UserItem::setConcernOrNotButtonHidden(bool flag)
{
    concernOrNotButton->setHidden(flag);
}

void UserItem::setLookingDetailButtonHidden(bool flag)
{
    lookingDetailButton->setHidden(flag);
}

UserItem::~UserItem()
{
    delete avatarLabel;
    delete userNameLabel;
    delete statisticLabel;
    delete concernOrNotButton;
    delete lookingDetailButton;
    delete infoLayout;
    delete mainLayout;
}
