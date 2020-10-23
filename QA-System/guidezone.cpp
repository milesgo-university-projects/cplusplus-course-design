#include "guidezone.h"

GuideZone::GuideZone(const int &mode,QWidget *parent):QWidget(parent)
{
    this->mode=mode;
    this->setFixedSize(140,630);
    avatarPix = new QLabel;
    userNameLabel = new QLabel;

    editPersonalInfo = new SimpleButton("","编辑个人信息");
    editPersonalInfo->setObjectName("editPersonalInfo");
    allQuestions = new SimpleButton("","全部提问");
    allQuestions->setObjectName("0");
    allMyQuetions = new SimpleButton("","我的提问");
    allMyQuetions->setObjectName("2");
    allMyAnswers = new SimpleButton("","我的回答");
    allMyAnswers->setObjectName("allMyAnswers");
    allMyConcernedQuestions = new SimpleButton("","我关注的提问");
    allMyConcernedQuestions->setObjectName("1");
    allMyFollowers = new SimpleButton("","我的粉丝");
    allMyFollowers->setObjectName("allMyFollowers");
    allMyConcernedUsers = new SimpleButton("","我关注的用户");
    allMyConcernedUsers->setObjectName("allMyConcernedUsers");

    signOutButton = new SimpleButton("","注销");
    signOutButton->setObjectName("signOut");

    addQuestionButton = new SimpleButton("","我要提问");
    addQuestionButton->setObjectName("addQuestion");

    this->setMode(mode);

    mainLayout = new QVBoxLayout;
    DivideWidget *divide;
    mainLayout->addWidget(avatarPix);
    mainLayout->addWidget(userNameLabel);
    divide = new DivideWidget(100,0);
    mainLayout->addWidget(divide);
    divideWidgets.push_back(divide);
    mainLayout->addWidget(addQuestionButton);
    divide = new DivideWidget(100,0);
    mainLayout->addWidget(divide);
    divideWidgets.push_back(divide);
    mainLayout->addWidget(editPersonalInfo);
    divide = new DivideWidget(100,0);
    mainLayout->addWidget(divide);
    divideWidgets.push_back(divide);
    mainLayout->addWidget(allQuestions);
    divide = new DivideWidget(100,0);
    mainLayout->addWidget(divide);
    divideWidgets.push_back(divide);
    mainLayout->addWidget(allMyQuetions);
    divide = new DivideWidget(100,0);
    mainLayout->addWidget(divide);
    divideWidgets.push_back(divide);
    mainLayout->addWidget(allMyAnswers);
    divide = new DivideWidget(100,0);
    mainLayout->addWidget(divide);
    divideWidgets.push_back(divide);
    mainLayout->addWidget(allMyConcernedQuestions);
    divide = new DivideWidget(100,0);
    mainLayout->addWidget(divide);
    divideWidgets.push_back(divide);
    mainLayout->addWidget(allMyFollowers);
    divide = new DivideWidget(100,0);
    mainLayout->addWidget(divide);
    divideWidgets.push_back(divide);
    mainLayout->addWidget(allMyConcernedUsers);
    divide = new DivideWidget(100,0);
    mainLayout->addWidget(divide);
    divideWidgets.push_back(divide);
    mainLayout->addWidget(signOutButton);
    divide = new DivideWidget(100,0);
    mainLayout->addWidget(divide);
    divideWidgets.push_back(divide);

    setLayout(mainLayout);
}

GuideZone::~GuideZone()
{
    delete avatarPix;
    delete userNameLabel;
    delete editPersonalInfo;
    delete allQuestions;
    delete allMyQuetions;
    delete allMyAnswers;
    delete allMyConcernedQuestions;
    delete allMyFollowers;
    delete allMyConcernedUsers;
    delete signOutButton;
    delete mainLayout;
    for(int i=0;i<divideWidgets.size();i++)
    {
        delete divideWidgets[i];
    }
    divideWidgets.clear();
}

void GuideZone::showEvent(QShowEvent *e)
{
    QString location="../data/user/avatar/"+QString("%1").arg(Overall::currentUserID)+".png";
    QFile file(location);
    if(!file.open(QIODevice::ReadOnly))
        location="../data/user/avatar/default.png";
    else
        file.close();
    avatarPix->setPixmap(Function::PixmapToRound(QPixmap(location),25));
    userNameLabel->setFont(QFont("Microsoft YaHei",10,75));
    userNameLabel->setText("       "+Overall::currentUserName);
    QWidget::showEvent(e);
}

void GuideZone::updateAvatarInfo()
{
    QString location="../data/user/avatar/"+QString("%1").arg(Overall::currentUserID)+".png";
    QFile file(location);
    if(!file.open(QIODevice::ReadOnly))
        location="../data/user/avatar/default.png";
    else
        file.close();
    avatarPix->setPixmap(Function::PixmapToRound(QPixmap(location),25));
}

void GuideZone::setMode(const int &mode)
{
    this->mode=mode;
    if(mode==0)
    {//查看自己的信息导航栏//全部提问按钮和注销按钮不变
        editPersonalInfo->setText("编辑个人信息");
        allMyQuetions->setText("我的提问");
        allMyAnswers->setText("我的回答");
        allMyConcernedQuestions->setText("我关注的提问");
        allMyFollowers->setText("我的粉丝");
        allMyConcernedUsers->setText("我关注的用户");
        addQuestionButton->setText("我要提问");//这个按钮名称不变，复用功能为返回我的导航栏
    }
    else if(mode==1)
    {//查看他人的信息导航栏
        editPersonalInfo->setText("他的个人信息");
        allMyQuetions->setText("他的提问");
        allMyAnswers->setText("他的回答");
        allMyConcernedQuestions->setText("他关注的提问");
        allMyFollowers->setText("他的粉丝");
        allMyConcernedUsers->setText("他关注的用户");
        addQuestionButton->setText("返回我的");//这个按钮名称不变，复用功能为返回我的导航栏
    }
}

int GuideZone::getMode()
{
    return mode;
}
