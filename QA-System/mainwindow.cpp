#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QWidget(parent)
{
    blankWidget = new QWidget;
    blankWidgetLayout = new QVBoxLayout;
    scrollArea = new QScrollArea;
    blankWidgetLayout->addWidget(scrollArea);
    blankWidget->setLayout(blankWidgetLayout);
    blankWidget->setFocusPolicy(Qt::NoFocus);

    currentFunctionLabel = new QLabel;
    rightLayout = new QVBoxLayout;
    rightLayout->addWidget(currentFunctionLabel);
    rightLayout->addWidget(blankWidget);

    blankLabel=NULL;
    personalInformationFunctionZone=NULL;
    userListFunctionZone=NULL;
    questionHeadListFunctionZone=NULL;
    questionDetailFunctionZone=NULL;
    answerListFunctionZone=NULL;
    addAnswerFunctionZone=NULL;
    addQuestionFunctionZone=NULL;

    scrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    scrollArea->setWidgetResizable(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(1025,705);
    titlebar = new titleBar;
    installEventFilter(titlebar);

    connect(titlebar->lastPageButton,SIGNAL(clicked()),this,SLOT(onRetreatButtonClicked()));
    guideZone = new GuideZone;

    downLayout = new QHBoxLayout;
    downLayout->addWidget(guideZone);
    downLayout->addLayout(rightLayout);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titlebar);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addLayout(downLayout);
    setLayout(mainLayout);

    connect(guideZone->editPersonalInfo,SIGNAL(clicked()),this,SLOT(onEditPersonalInformationButtonClicked()));
    connect(guideZone->allMyFollowers,SIGNAL(clicked()),this,SLOT(onUserListButtonClicked()));
    connect(guideZone->allMyConcernedUsers,SIGNAL(clicked()),this,SLOT(onUserListButtonClicked()));
    connect(guideZone->allQuestions,SIGNAL(clicked()),this,SLOT(onAllQuestionsButtonClicked()));
    connect(guideZone->allMyQuetions,SIGNAL(clicked()),this,SLOT(onAllQuestionsButtonClicked()));
    connect(guideZone->allMyConcernedQuestions,SIGNAL(clicked()),this,SLOT(onAllQuestionsButtonClicked()));
    connect(guideZone->allMyAnswers,SIGNAL(clicked()),this,SLOT(onAllMyAnswersButtonClicked()));
    connect(guideZone->signOutButton,SIGNAL(clicked()),this,SLOT(onSignOutButtonClicked()));
    connect(guideZone->addQuestionButton,SIGNAL(clicked()),this,SLOT(onAddQuestionButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete titlebar;
    delete guideZone;
    delete currentFunctionLabel;
    if(blankLabel!=NULL)
        delete blankLabel;
    if(personalInformationFunctionZone!=NULL)
        delete personalInformationFunctionZone;
    if(userListFunctionZone!=NULL)
        delete userListFunctionZone;
    if(questionHeadListFunctionZone!=NULL)
        delete questionHeadListFunctionZone;
    if(questionDetailFunctionZone!=NULL)
        delete questionDetailFunctionZone;
    if(answerListFunctionZone!=NULL)
        delete answerListFunctionZone;
    if(addAnswerFunctionZone!=NULL)
        delete addAnswerFunctionZone;
    if(addQuestionFunctionZone!=NULL)
        delete addQuestionFunctionZone;
    delete rightLayout;
    delete downLayout;
    delete mainLayout;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    writeAllUsers();
    writeAllQuestions();
    writeALLAnswers();
    User::writeUserNameToID();//读取用户名和ID的映射
    User::writeUserIDToPassword();//读取ID和密码的映射
    Answer::writeAnswerIDToQuestionID();//读取答案ID和问题ID的映射
    Answer::writeAnswerIDToUserID();//读取答案ID和回答者ID的映射
    Question::writeQuestionIDToUserID();//读取问题和提问者ID的映射
    QWidget::closeEvent(e);
}

void MainWindow::deleteCurrentFunctionZone()
{
    if(blankLabel!=NULL)
    {
        delete blankLabel;
        blankLabel=NULL;
    }
    else if(personalInformationFunctionZone!=NULL)
    {
        delete personalInformationFunctionZone;
        personalInformationFunctionZone=NULL;
    }
    else if(userListFunctionZone!=NULL)
    {
        delete userListFunctionZone;
        userListFunctionZone=NULL;
    }
    else if(questionHeadListFunctionZone!=NULL)
    {
        delete questionHeadListFunctionZone;
        questionHeadListFunctionZone=NULL;
    }
    else if(questionDetailFunctionZone!=NULL)
    {
        delete questionDetailFunctionZone;
        questionDetailFunctionZone=NULL;
    }
    else if(answerListFunctionZone!=NULL)
    {
        delete answerListFunctionZone;
        answerListFunctionZone=NULL;
    }
    else if(addAnswerFunctionZone!=NULL)
    {
        delete addAnswerFunctionZone;
        addAnswerFunctionZone=NULL;
    }
    else if(addQuestionFunctionZone!=NULL)
    {
        delete addQuestionFunctionZone;
        addQuestionFunctionZone=NULL;
    }
}

void MainWindow::onEditPersonalInformationButtonClicked()
{
    Overall::windowControl=true;
    deleteCurrentFunctionZone();
    if(guideZone->getMode()==0)
    {//当前登录用户的编辑模式
        currentFunctionLabel->setText("编辑用户信息");
        personalInformationFunctionZone=new EditPersonalInformation(Overall::currentUserID,0);
        connect(personalInformationFunctionZone,SIGNAL(userInfoUpdated(class User)),this,SLOT(updateUserInfo(class User)));
    }
    else if(guideZone->getMode()==1)
    {//其他用户的查看模式//waiting for you
        QString userName=" "+Overall::mainWindow->getUserName(Overall::currentLookingUserID)+" ";
        currentFunctionLabel->setText("查看"+userName+"的个人信息");
        personalInformationFunctionZone=new EditPersonalInformation(Overall::currentLookingUserID,1);
    }
    scrollArea->setWidget(personalInformationFunctionZone);
    connect(personalInformationFunctionZone,SIGNAL(avatarChangedSignal()),guideZone,SLOT(updateAvatarInfo()));
}

void MainWindow::onAllQuestionsButtonClicked()
{
    Overall::windowControl=true;
    deleteCurrentFunctionZone();
    QObject *object=sender();
    int mode=object->objectName().toInt();
    if(mode==0)
    {
        questionHeadListFunctionZone = new QuestionHeadLineList(mode,Overall::currentUserID);
        currentFunctionLabel->setText("全部提问");
    }
    else if(mode==1)
    {
        if(guideZone->getMode()==0)
        {
            currentFunctionLabel->setText("我关注的提问");
            questionHeadListFunctionZone = new QuestionHeadLineList(mode,Overall::currentUserID);
        }
        else if(guideZone->getMode()==1)
        {
            QString userName=" "+Overall::mainWindow->getUserName(Overall::currentLookingUserID)+" ";
            currentFunctionLabel->setText(userName+"关注的提问");
            questionHeadListFunctionZone = new QuestionHeadLineList(mode,Overall::currentLookingUserID);
        }
    }
    else if(mode==2)
    {
        if(guideZone->getMode()==0)
        {
            currentFunctionLabel->setText("我的提问");
            questionHeadListFunctionZone = new QuestionHeadLineList(mode,Overall::currentUserID);
        }
        else if(guideZone->getMode()==1)
        {
            QString userName=" "+Overall::mainWindow->getUserName(Overall::currentLookingUserID)+" ";
            currentFunctionLabel->setText(userName+"的提问");
            questionHeadListFunctionZone = new QuestionHeadLineList(mode,Overall::currentLookingUserID);
        }
    }
    scrollArea->setWidget(questionHeadListFunctionZone);
}

void MainWindow::onUserListButtonClicked()
{
    Overall::windowControl=true;
    QObject *object=sender();
    deleteCurrentFunctionZone();
    if(object->objectName()=="allMyFollowers")
    {
        if(guideZone->getMode()==0)
        {
            currentFunctionLabel->setText("我的粉丝");
            userListFunctionZone = new UserListWidget(0,Overall::currentUserID);
        }
        else if(guideZone->getMode()==1)
        {
            QString userName=" "+Overall::mainWindow->getUserName(Overall::currentLookingUserID)+" ";
            currentFunctionLabel->setText(userName+"的粉丝");
            userListFunctionZone = new UserListWidget(0,Overall::currentLookingUserID);
        }
    }
    else if(object->objectName()=="allMyConcernedUsers")
    {
        if(guideZone->getMode()==0)
        {
            currentFunctionLabel->setText("我关注的用户");
            userListFunctionZone = new UserListWidget(1,Overall::currentUserID);
        }
        else if(guideZone->getMode()==1)
        {
            QString userName=" "+Overall::mainWindow->getUserName(Overall::currentLookingUserID)+" ";
            currentFunctionLabel->setText(userName+"关注的用户");
            userListFunctionZone = new UserListWidget(1,Overall::currentLookingUserID);
        }
    }
    scrollArea->setWidget(userListFunctionZone);
}

void MainWindow::onAllMyAnswersButtonClicked()
{
    Overall::windowControl=true;
    deleteCurrentFunctionZone();
    if(guideZone->getMode()==0)
    {
        currentFunctionLabel->setText("我的回答");
        answerListFunctionZone = new MyAnswerList(Overall::currentUserID);
    }
    else if(guideZone->getMode()==1)
    {
        QString userName=" "+Overall::mainWindow->getUserName(Overall::currentLookingUserID)+" ";
        currentFunctionLabel->setText(userName+"的回答");
        answerListFunctionZone = new MyAnswerList(Overall::currentLookingUserID);
    }
    scrollArea->setWidget(answerListFunctionZone);
}

void MainWindow::ShowQuestion(const int &questionID)
{
    currentFunctionLabel->setText("提问详情");
    Overall::windowControl=true;
    deleteCurrentFunctionZone();
    questionDetailFunctionZone = new QuestionDetailWidget(5);
    questionDetailFunctionZone->setModeAndInfo(0,questionID);
    scrollArea->setWidget(questionDetailFunctionZone);
}

void MainWindow::showBackgournd()
{
    currentFunctionLabel->setText("开始界面");
    deleteCurrentFunctionZone();
    blankLabel = new QLabel;
    blankLabel->setPixmap(QPixmap("../data/images/background.png"));
    scrollArea->setWidget(blankLabel);
}

void MainWindow::onAddAnswerButtonClicked(const int &userID,const int &questionID)
{
    currentFunctionLabel->setText("编辑回答");
    Overall::windowControl=true;
    deleteCurrentFunctionZone();
    addAnswerFunctionZone = new AddAnswerPage(userID,questionID);
    scrollArea->setWidget(addAnswerFunctionZone);
}

void MainWindow::onAddQuestionButtonClicked()
{
    if(getGuideZoneMode()==0)
    {
        currentFunctionLabel->setText("编辑提问");
        Overall::windowControl=true;
        deleteCurrentFunctionZone();
        addQuestionFunctionZone = new AddQuestionPage;
        scrollArea->setWidget(addQuestionFunctionZone);
    }
    else if(getGuideZoneMode()==1)
    {
        currentFunctionLabel->setText("编辑用户信息");
        setGuideZoneMode(0);
        Overall::windowControl=true;
        deleteCurrentFunctionZone();
        personalInformationFunctionZone = new EditPersonalInformation(Overall::currentUserID);
        scrollArea->setWidget(personalInformationFunctionZone);
    }
}

void MainWindow::questionContainsSomeString(const QString &content)
{//windowControl还未加入
    currentFunctionLabel->setText("搜索结果");
    Overall::windowControl=true;
    deleteCurrentFunctionZone();
    questionHeadListFunctionZone = new QuestionHeadLineList(content);
    scrollArea->setWidget(questionHeadListFunctionZone);
}

void MainWindow::questionBetweenSomeDateTime(const QDateTime &startDateTime,const QDateTime &endDateTime)
{
    currentFunctionLabel->setText("搜索结果");
    Overall::windowControl=true;
    deleteCurrentFunctionZone();
    questionHeadListFunctionZone = new QuestionHeadLineList(startDateTime,endDateTime);
    scrollArea->setWidget(questionHeadListFunctionZone);
}

void MainWindow::onRetreatButtonClicked()
{
    if(Overall::windowStack.size()==1)
        return;
    Overall::windowControl=false;
    deleteCurrentFunctionZone();
    int number=Overall::windowStack.pop();
    if(number==12)
    {
        Overall::contentStack.pop();
    }
    else if(number==13)
    {
        Overall::startDateTimeStack.pop();
        Overall::endDateTimeStack.pop();
    }
    number=Overall::windowStack.top();
    int loc=Overall::windowStack.size()-1;
    int mineOrHis=Overall::stackLocationToMineOrHis[loc];
    setGuideZoneMode(mineOrHis);
    switch(number)
    {
        case 0:
        {//主界面
            currentFunctionLabel->setText("开始界面");
            showBackgournd();
            break;
        }
        case 1:
        {//编辑信息的界面，需要userID
            int userID=Overall::stackLocationToID[loc];
            if(mineOrHis==1)
                Overall::currentLookingUserID=userID;
            currentFunctionLabel->setText("编辑用户信息");
            personalInformationFunctionZone=new EditPersonalInformation(userID,0);
            scrollArea->setWidget(personalInformationFunctionZone);
            connect(personalInformationFunctionZone,SIGNAL(userInfoUpdated(class User)),this,SLOT(updateUserInfo(class User)));
            break;
        }
        case 2:
        {//查看信息的界面
            int userID=Overall::stackLocationToID[loc];
            if(mineOrHis==1)
                Overall::currentLookingUserID=userID;
            QString userName=" "+Overall::mainWindow->getUserName(userID)+" ";
            currentFunctionLabel->setText("查看"+userName+"的个人信息");
            personalInformationFunctionZone=new EditPersonalInformation(userID,1);
            scrollArea->setWidget(personalInformationFunctionZone);
            break;
        }
        case 3:
        {//查看提问详情的界面
            currentFunctionLabel->setText("提问详情");
            questionDetailFunctionZone = new QuestionDetailWidget(5);
            questionDetailFunctionZone->setModeAndInfo(0,Overall::stackLocationToID[loc]);
            scrollArea->setWidget(questionDetailFunctionZone);
            break;
        }
        case 4:
        {//查看全部提问的界面
            currentFunctionLabel->setText("全部提问");
            questionHeadListFunctionZone = new QuestionHeadLineList(0);
            scrollArea->setWidget(questionHeadListFunctionZone);
            break;
        }
        case 5:
        {//查看某用户的关注提问的界面
            int userID=Overall::stackLocationToID[loc];
            if(mineOrHis==1)
                Overall::currentLookingUserID=userID;
            QString userName="我";
            if(userID!=Overall::currentUserID)
                userName=" "+Overall::mainWindow->getUserName(userID)+" ";
            currentFunctionLabel->setText(userName+"关注的提问");
            questionHeadListFunctionZone = new QuestionHeadLineList(1,userID);
            scrollArea->setWidget(questionHeadListFunctionZone);
            break;
        }
        case 6:
        {//查看某用户的提问的界面
            int userID=Overall::stackLocationToID[loc];
            if(mineOrHis==1)
                Overall::currentLookingUserID=userID;
            QString userName="我";
            if(userID!=Overall::currentUserID)
                userName=" "+Overall::mainWindow->getUserName(userID)+" ";
            currentFunctionLabel->setText(userName+"的提问");
            questionHeadListFunctionZone = new QuestionHeadLineList(2,userID);
            scrollArea->setWidget(questionHeadListFunctionZone);
            break;
        }
        case 7:
        {//查看某用户全部粉丝的界面
            int userID=Overall::stackLocationToID[loc];
            if(mineOrHis==1)
                Overall::currentLookingUserID=userID;
            QString userName="我";
            if(userID!=Overall::currentUserID)
                userName=" "+Overall::mainWindow->getUserName(userID)+" ";
            currentFunctionLabel->setText(userName+"的粉丝");
            userListFunctionZone = new UserListWidget(0,userID);
            scrollArea->setWidget(userListFunctionZone);
            break;
        }
        case 8:
        {//查看某用户全部关注用户的界面
            int userID=Overall::stackLocationToID[loc];
            if(mineOrHis==1)
                Overall::currentLookingUserID=userID;
            QString userName="我";
            if(userID!=Overall::currentUserID)
                userName=" "+Overall::mainWindow->getUserName(userID)+" ";
            currentFunctionLabel->setText(userName+"关注的用户");
            userListFunctionZone = new UserListWidget(1,userID);
            scrollArea->setWidget(userListFunctionZone);
            break;
        }
        case 9:
        {//查看某用户全部回答列表的界面
            int userID=Overall::stackLocationToID[loc];
            if(mineOrHis==1)
                Overall::currentLookingUserID=userID;
            QString userName="我";
            if(userID!=Overall::currentUserID)
                userName=" "+Overall::mainWindow->getUserName(userID)+" ";
            currentFunctionLabel->setText(userName+"的回答");
            answerListFunctionZone = new MyAnswerList(userID);
            scrollArea->setWidget(answerListFunctionZone);
            break;
        }
        case 10:
        {//编辑回答的界面
            currentFunctionLabel->setText("编辑回答");
            addAnswerFunctionZone = new AddAnswerPage(Overall::currentUserID,Overall::stackLocationToID[loc]);
            scrollArea->setWidget(addAnswerFunctionZone);
            break;
        }
        case 11:
        {//编辑提问的界面
            currentFunctionLabel->setText("编辑提问");
            addQuestionFunctionZone = new AddQuestionPage;
            scrollArea->setWidget(addQuestionFunctionZone);
            break;
        }
        case 12:
        {//按照提问标题搜索
            currentFunctionLabel->setText("搜索结果");
            QString content=Overall::contentStack.top();
            questionHeadListFunctionZone = new QuestionHeadLineList(content);
            scrollArea->setWidget(questionHeadListFunctionZone);
            break;
        }
        case 13:
        {//按照提问发布时间搜索
            currentFunctionLabel->setText("搜索结果");
            QDateTime startDateTime=Overall::startDateTimeStack.top();
            QDateTime endDateTime=Overall::endDateTimeStack.top();
            questionHeadListFunctionZone = new QuestionHeadLineList(startDateTime,endDateTime);
            scrollArea->setWidget(questionHeadListFunctionZone);
            break;
        }
        default:
            break;
    }
}

void MainWindow::showEvent(QShowEvent *e)
{
    Overall::windowStack.push(0);
    showBackgournd();
    readAllUsers();
    readAllAnswers();
    readAllQuestions();
    setGuideZoneMode(0);
    QWidget::showEvent(e);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

    const int m_nBorder=5;
    MSG *param = static_cast<MSG *>(message);

    switch (param->message)
    {
        case WM_NCHITTEST:
        {
            int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
            int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

            // 如果鼠标位于子控件上，则不进行处理
            if (childAt(nX, nY) != NULL)
                return QWidget::nativeEvent(eventType, message, result);

            *result = HTCAPTION;

            // 鼠标区域位于窗体边框，进行缩放
            if ((nX > 0) && (nX < m_nBorder))
                *result = HTLEFT;

            if ((nX > this->width() - m_nBorder) && (nX < this->width()))
                *result = HTRIGHT;

            if ((nY > 0) && (nY < m_nBorder))
                *result = HTTOP;

            if ((nY > this->height() - m_nBorder) && (nY < this->height()))
                *result = HTBOTTOM;

            if ((nX > 0) && (nX < m_nBorder) && (nY > 0)
                    && (nY < m_nBorder))
                *result = HTTOPLEFT;

            if ((nX > this->width() - m_nBorder) && (nX < this->width())
                    && (nY > 0) && (nY < m_nBorder))
                *result = HTTOPRIGHT;

            if ((nX > 0) && (nX < m_nBorder)
                    && (nY > this->height() - m_nBorder) && (nY < this->height()))
                *result = HTBOTTOMLEFT;

            if ((nX > this->width() - m_nBorder) && (nX < this->width())
                    && (nY > this->height() - m_nBorder) && (nY < this->height()))
                *result = HTBOTTOMRIGHT;

            return true;
        }
        default:
            break;
    }
    return QWidget::nativeEvent(eventType, message, result);
}


void MainWindow::readAllUsers()
{
    QString path;
    QFile file;
    int ID,userCnt=0;
    userList.clear();
    userIDToListLocation.clear();
    for(QMap<QString,int>::iterator it=User::userNameToID.begin();it!=User::userNameToID.end();it++)
    {
        class User tmpUser;
        ID=it.value();
        tmpUser.setUserID(ID);
        tmpUser.setUserName(User::IDToUserName[ID]);
        try
        {
            path="../data/user/personal information/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readallusers.function personal information.file");
                tmpUser.setGender(2);
                tmpUser.setBirthday(QDate(2000,1,1));
            }
            else
            {
                QTextStream in(&file);
                Overall::userReadWriteFlag=0;//读personal information
                in>>tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/personal introduction/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readallusers.function personal introduction.file");
                tmpUser.setIntroduction("");
            }
            else
            {
                QTextStream in(&file);
                Overall::userReadWriteFlag=1;
                in>>tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/answers/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readallusers.function answers.file");
                tmpUser.clearMyAnswers();
            }
            else
            {
                QTextStream in(&file);
                Overall::userReadWriteFlag=2;
                in>>tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/fans/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readallusers.function fans.file");
                tmpUser.clearFans();
            }
            else
            {
                QTextStream in(&file);
                Overall::userReadWriteFlag=3;
                in>>tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/concerners/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readalluser.cpp concerners.file");
                tmpUser.clearConcernUsers();
            }
            else
            {
                QTextStream in(&file);
                Overall::userReadWriteFlag=4;
                in>>tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/questions/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readalluser.function questions.file");
                tmpUser.clearMyQuestions();
            }
            else
            {
                QTextStream in(&file);
                Overall::userReadWriteFlag=5;
                in>>tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/concern questions/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readalluser.function concern questions.file");
                tmpUser.clearConcernQuestions();
            }
            else
            {
                QTextStream in(&file);
                Overall::userReadWriteFlag=6;
                in>>tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        userIDToListLocation[ID]=userCnt++;
        userList.push_back(tmpUser);
    }
}

void MainWindow::writeAllUsers()
{
    QString path;
    QFile file;
    for(QMap<QString,int>::iterator it=User::userNameToID.begin();it!=User::userNameToID.end();it++)
    {
        int ID=it.value();
        int loc=userIDToListLocation[ID];
        class User tmpUser=userList[loc];

        try
        {
            path="../data/user/personal information/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallusers.function personal information.file");
            }
            else
            {
                QTextStream out(&file);
                Overall::userReadWriteFlag=0;
                out<<tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/personal introduction/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writealluser.function personal introduction.file");
            }
            else
            {
                QTextStream out(&file);
                Overall::userReadWriteFlag=1;
                out<<tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/answers/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallusers.function answers.file");
            }
            else
            {
                QTextStream out(&file);
                Overall::userReadWriteFlag=2;
                out<<tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/fans/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallusers.function fans.file");
            }
            else
            {
                QTextStream out(&file);
                Overall::userReadWriteFlag=3;
                out<<tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/concerners/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallusers.function concerners.file");
            }
            else
            {
                QTextStream out(&file);
                Overall::userReadWriteFlag=4;
                out<<tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/questions/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writealluser.function questions.file");
            }
            else
            {
                QTextStream out(&file);
                Overall::userReadWriteFlag=5;
                out<<tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            path="../data/user/concern questions/"+QString("%1").arg(ID)+".txt";
            file.setFileName(path);
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallusers.function concern question.file");
            }
            else
            {
                QTextStream out(&file);
                Overall::userReadWriteFlag=6;
                out<<tmpUser;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }
    }
}

void MainWindow::updateUserInfo(User tmpUser)
{
    int loc=userIDToListLocation[Overall::currentUserID];
    userList[loc]=tmpUser;
}

bool MainWindow::checkISAconcerningB(const int &A, const int &B)
{
    int loc=userIDToListLocation[B];
    class User tmpUser=userList[loc];
    return tmpUser.isConcernedBy(A);
}

void MainWindow::makeAconcernB(const int &A, const int &B,bool flag)
{
    int loc=userIDToListLocation[B];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp makeAconcernB.function";
        exit(0);
    }
    if(flag)
        userList[loc].addFans(A);
    else
        userList[loc].deleteFans(A);
    loc=userIDToListLocation[A];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp makeAconcernB.function";
        exit(0);
    }
    if(flag)
        userList[loc].addConcernUsers(B);
    else
        userList[loc].deleteConcernUsers(B);
}


void MainWindow::readAllAnswers()
{//未测试
    answerIDToAnswerObject.clear();
    for(QMap<int,int>::iterator it=Answer::answerIDToUserID.begin();it!=Answer::answerIDToUserID.end();it++)
    {
        class Answer tmpAnswer;
        int infoID=it.key();
        tmpAnswer.setInfoID(infoID);
        tmpAnswer.setUserID(it.value());
        QFile file;

        try
        {
            file.setFileName("../data/answers/information/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error int mainwindow.cpp writeallanswer.function information.file");
                tmpAnswer.setDateTime(QDateTime(QDate(2000,1,1),QTime(12,0,0)));
            }
            else
            {
                Overall::answerReadWriteFlag=0;
                QTextStream in(&file);
                in>>tmpAnswer;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            file.setFileName("../data/answers/content/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readallanswers.function content.file");
                tmpAnswer.setContent("");
            }
            else
            {
                Overall::answerReadWriteFlag=1;
                QTextStream in(&file);
                in>>tmpAnswer;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            file.setFileName("../data/answers/praisers/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                tmpAnswer.clearPraisers();
                throw QString("open file error in mainwindow.cpp readallanswers.function praisers.file");
            }
            else
            {
                Overall::answerReadWriteFlag=2;
                QTextStream in(&file);
                in>>tmpAnswer;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        answerIDToAnswerObject[infoID]=tmpAnswer;
    }
}

void MainWindow::writeALLAnswers()
{//未测试
    for(QMap<int,class Answer>::iterator it=answerIDToAnswerObject.begin();it!=answerIDToAnswerObject.end();it++)
    {
        class Answer tmpAnswer=it.value();
        int infoID=it.key();
        QFile file;

        try
        {
            file.setFileName("../data/answers/information/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallanswer.function information.file");
            }
            else
            {
                Overall::answerReadWriteFlag=0;
                QTextStream out(&file);
                out<<tmpAnswer;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            file.setFileName("../data/answers/content/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallanswers.function content.file");
            }
            else
            {
                Overall::answerReadWriteFlag=1;
                QTextStream out(&file);
                out<<tmpAnswer;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            file.setFileName("../data/answers/praisers/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallanswers.function praisers.file");
            }
            else
            {
                Overall::answerReadWriteFlag=2;
                QTextStream out(&file);
                out<<tmpAnswer;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }
    }
}

void MainWindow::readAllQuestions()
{//未测试
    questionIDToQuestionObject.clear();
    for(QMap<int,int>::iterator it=Question::questionIDToUserID.begin();it!=Question::questionIDToUserID.end();it++)
    {
        class Question tmpQuestion;
        int infoID=it.key();
        tmpQuestion.setInfoID(infoID);
        tmpQuestion.setUserID(Question::questionIDToUserID[infoID]);

        QFile file;

        try
        {
            file.setFileName("../data/questions/answerList/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readallquestions.function answerlist.file");
                tmpQuestion.clearAnswer();
            }
            else
            {
                Overall::questionReadWriteFlag=0;
                QTextStream in(&file);
                in>>tmpQuestion;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            file.setFileName("../data/questions/title/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readallquestions.function title.file");
                tmpQuestion.setTitle("");
            }
            else
            {
                Overall::questionReadWriteFlag=1;
                QTextStream in(&file);
                in>>tmpQuestion;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            file.setFileName("../data/questions/detail/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readallquestions.function detail.file");
                tmpQuestion.setContent("");
            }
            else
            {
                Overall::questionReadWriteFlag=2;
                QTextStream in(&file);
                in>>tmpQuestion;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            file.setFileName("../data/questions/information/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp readallquestion.function information.file");
                tmpQuestion.setDateTime(QDateTime(QDate(2000,0,0),QTime(12,0,0)));
            }
            else
            {
                Overall::questionReadWriteFlag=3;
                QTextStream in(&file);
                in>>tmpQuestion;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        questionIDToQuestionObject[infoID]=tmpQuestion;
    }
}

void MainWindow::writeAllQuestions()
{//未测试
    for(QMap<int,class Question>::iterator it=questionIDToQuestionObject.begin();it!=questionIDToQuestionObject.end();it++)
    {
        class Question tmpQuestion=it.value();
        int infoID=it.key();

        QFile file;

        try
        {
            file.setFileName("../data/questions/answerList/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallquestions.function answerlist.file");
            }
            else
            {
                Overall::questionReadWriteFlag=0;
                QTextStream out(&file);
                out<<tmpQuestion;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            file.setFileName("../data/questions/title/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallquestions.function title.file");
            }
            else
            {
                Overall::questionReadWriteFlag=1;
                QTextStream out(&file);
                out<<tmpQuestion;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            file.setFileName("../data/questions/detail/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallquestions.function detail.file");
            }
            else
            {
                Overall::questionReadWriteFlag=2;
                QTextStream out(&file);
                out<<tmpQuestion;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }

        try
        {
            file.setFileName("../data/questions/information/"+QString("%1").arg(infoID)+".txt");
            if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                throw QString("open file error in mainwindow.cpp writeallquestion.function information.file");
            }
            else
            {
                Overall::questionReadWriteFlag=3;
                QTextStream out(&file);
                out<<tmpQuestion;
                file.close();
            }
        }
        catch(QString error)
        {
            qDebug()<<error;
        }
    }
}

QString MainWindow::getUserName(const int &userID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp getUserName.function";
        exit(0);
    }
    return userList[loc].getUserName();
}

bool MainWindow::isAnswerPraisedByUser(const int &answerID, const int &userID)
{
    return answerIDToAnswerObject[answerID].isPraisedBy(userID);
}

void MainWindow::addPraiser(const int &answerID,const int &userID)
{
    answerIDToAnswerObject[answerID].addPraiser(userID);
}

void MainWindow::deletePraiser(const int &answerID, const int &userID)
{
    answerIDToAnswerObject[answerID].deletePraiser(userID);
}

void MainWindow::deleteAconcerningB(const int &A, const int &B)
{
    int loc=userIDToListLocation[A];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp deleteAconcerningB.function";
        exit(0);
    }
    userList[loc].deleteConcernUsers(B);
    loc=userIDToListLocation[B];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp deleteAconcerningB.function";
        exit(0);
    }
    userList[loc].deleteFans(A);
}

void MainWindow::addAconcerningB(const int &A, const int &B)
{
    int loc=userIDToListLocation[A];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp addAconcerningB.function";
        exit(0);
    }
    userList[loc].addConcernUsers(B);
    loc=userIDToListLocation[B];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp addAconcerningB.function";
        exit(0);
    }
    userList[loc].addFans(A);
}

bool MainWindow::isUserAconcerningQuestionB(const int &userID, const int questionID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp isUserAconcerningQuestionB.function";
        exit(0);
    }
    return userList[loc].isConcerningQuestion(questionID);
}

void MainWindow::addConcerningQuestion(const int &userID, const int questionID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp addConcerningQuestion.function";
        exit(0);
    }
    userList[loc].addConcernQuetions(questionID);
}

void MainWindow::deleteConcerningQuestion(const int &userID, const int questionID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp deleteConcerningQuestion.function";
        exit(0);
    }
    userList[loc].deleteConcernQuestions(questionID);
}

QSet<int> MainWindow::getConcernedQuestionSet(const int &userID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp getConcernedQuestionSet.function";
        exit(0);
    }
    return userList[loc].getConcernQuetions();
}

QSet<int> MainWindow::getQuestionSet(const int &userID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp getQuestionSet.function";
        exit(0);
    }
    return userList[loc].getMyQuestions();
}

QSet<int> MainWindow::getMyAnswerSet(const int &userID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp getMyAnswerSet.function";
        exit(0);
    }
    return userList[loc].getMyAnswers();
}

class User MainWindow::getUserClass(const int &userID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp getUserClass.function";
        exit(0);
    }
    return userList[loc];
}

QSet<int> MainWindow::getConcernUserSet(const int &userID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp getConcernUserSet.function";
        exit(0);
    }
    return userList[loc].getconcernUsers();
}

QSet<int> MainWindow::getFansUserSet(const int &userID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp getFansUserSet.function";
        exit(0);
    }
    return userList[loc].getFans();
}

void MainWindow::onSignOutButtonClicked()
{
    emit loginAgain();
    Overall::windowStack.clear();
    this->close();
}

QDateTime MainWindow::getAnswerDateTime(const int &answerID)
{
    return answerIDToAnswerObject[answerID].getDateTime();
}

QDateTime MainWindow::getQuestionDateTime(const int &questionID)
{
    return questionIDToQuestionObject[questionID].getDateTime();
}

void MainWindow::updateAvatarInfo()
{
    guideZone->updateAvatarInfo();
}

int MainWindow::getUserAnswerQuestionID(const int &userID, const int &questionID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp getUserAnswerQuestionID.function";
        exit(0);
    }
    return userList[loc].getAnswerID(questionID);
}

QString MainWindow::getAnswerContent(const int &answerID)
{
    return answerIDToAnswerObject[answerID].getContent();
}

void MainWindow::addAnswerOfUser(const int &answerID, const int &userID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp addAnswerOfUser.function";
        exit(0);
    }
    userList[loc].addMyAnswers(answerID);
}

void MainWindow::addAnswerOfQuestion(const int &answerID, const int &questionID)
{
    questionIDToQuestionObject[questionID].addAnswer(answerID);
}

void MainWindow::addQuestionOfUser(const int &questionID,const int &userID)
{
    int loc=userIDToListLocation[userID];
    if(loc>=userList.size())
    {
        qDebug()<<"out of range in mainwindow.cpp addQuestionOfUser.function";
        exit(0);
    }
    userList[loc].addMyQuestions(questionID);
}

int MainWindow::getGuideZoneMode()
{
    return guideZone->getMode();
}

void MainWindow::setGuideZoneMode(const int &mode)
{
    guideZone->setMode(mode);
}

int MainWindow::getAnswerPraiseNum(const int &answerID)
{
    return answerIDToAnswerObject[answerID].getPraiseNum();
}
