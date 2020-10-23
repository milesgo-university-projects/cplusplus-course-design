#include "questiontitleanddetail.h"

QuestionTitleAndDetail::QuestionTitleAndDetail(QWidget *parent):QFrame(parent)
{
    this->setStyleSheet("background-color: rgb(90,90,90)");
    titleLabel = new QLabel;
    titleLabel->setFont(QFont("Microsoft YaHei",15,75));
    titleLabel->adjustSize();
    titleLabel->setWordWrap(true);
    detailLabel = new QLabel;
    detailLabel->setFont(QFont("Microsoft YaHei",12,50));
    detailLabel->adjustSize();
    detailLabel->setWordWrap(true);
    userNameLabel = new QLabel;
    userNameLabel->setFont(QFont("Microsoft YaHei",12,50));
    dateTimeLabel = new QLabel;
    dateTimeLabel->setFont(QFont("Microsoft YaHei",12,50));
    answerAmountLabel = new QLabel;
    answerAmountLabel->setFont(QFont("Microsoft YaHei",12,50));

    infoLayout = new QHBoxLayout;

    sortButton = new QPushButton;
    sortButton->setFocusPolicy(Qt::NoFocus);
    sortButton->setText("点击按赞数排序");
    intoDetailButton = new QPushButton;
    intoDetailButton->setFocusPolicy(Qt::NoFocus);
    intoDetailButton->setText("显示详情");
    intoDetailButton->setFixedWidth(75);
    concernUserButton = new QPushButton;
    concernUserButton->setFocusPolicy(Qt::NoFocus);
    concernUserButton->setFixedWidth(100);
    concernQuestionButton = new QPushButton;
    concernQuestionButton->setFocusPolicy(Qt::NoFocus);
    concernQuestionButton->setFixedWidth(100);
    addOrChangeAnswerButton = new QPushButton;
    addOrChangeAnswerButton->setFocusPolicy(Qt::NoFocus);
    addOrChangeAnswerButton->setFixedWidth(100);


    buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(30);
    buttonLayout->addWidget(concernUserButton,2);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(concernQuestionButton,2);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(sortButton,2);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(intoDetailButton,2);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(addOrChangeAnswerButton,2);
    buttonLayout->addStretch(0);

    mainLayout = new QVBoxLayout;

    infoLayout->addStretch(20);
    infoLayout->addWidget(userNameLabel,3);
    infoLayout->addStretch(1);
    infoLayout->addWidget(dateTimeLabel,3);
    infoLayout->addStretch(1);
    infoLayout->addWidget(answerAmountLabel,3);
    infoLayout->addStretch(0);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(detailLabel);
    mainLayout->addLayout(infoLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(intoDetailButton,SIGNAL(clicked()),this,SLOT(onIntoDetailButtonClicked()));
    connect(concernUserButton,SIGNAL(clicked()),this,SLOT(onConcernUserButtonClicked()));
    connect(concernQuestionButton,SIGNAL(clicked()),this,SLOT(onConcernQuestionButtonClicked()));
    connect(sortButton,SIGNAL(clicked()),this,SLOT(onSortButtonClicked()));
}

void QuestionTitleAndDetail::setInfo(QString title, QString detail, QDateTime dateTime, QString userName,int answerAmount,int userID,int questionID)
{
    this->userID=userID;
    this->questionID=questionID;
    this->setStyleSheet("background-color: rgb(90,90,90)");
    titleLabel->setText(title);
    detailLabel->setText(detail);
    dateTimeLabel->setText(QString("时间：%1年%2月%3日%4时%5分").arg(dateTime.date().year()).arg(dateTime.date().month()).arg(dateTime.date().day()).arg(dateTime.time().hour()).arg(dateTime.time().minute()));
    userNameLabel->setText("提问者："+userName);
    answerAmountLabel->setText(QString("共%1回答").arg(answerAmount));

    sortButton->setText("点击按赞数排序");
    sortButton->setEnabled(true);
    sortButton->setStyleSheet("border-width: 1px");
    intoDetailButton->setText("显示详情");
    intoDetailButton->setEnabled(true);
    intoDetailButton->setStyleSheet("border-width: 1px");
    concernQuestionButton->setEnabled(true);
    concernQuestionButton->setStyleSheet("border-width: 1px");
    addOrChangeAnswerButton->setEnabled(true);
    addOrChangeAnswerButton->setStyleSheet("border-width: 1px");

    if(Overall::currentUserID==userID)
    {
        concernUserButton->setEnabled(false);
        concernUserButton->setStyleSheet("border-width: 0px");
        concernUserButton->setText("");
    }
    else
    {
        concernUserButton->setEnabled(true);
        concernUserButton->setStyleSheet("border-width: 1px");
        if(Overall::mainWindow->checkISAconcerningB(Overall::currentUserID,userID))
        {
            isAuthorConcerned=true;
            concernUserButton->setText("取消关注提问者");
        }
        else
        {
            isAuthorConcerned=false;
            concernUserButton->setText("关注提问者");
        }
    }
    if(Overall::mainWindow->isUserAconcerningQuestionB(Overall::currentUserID,questionID))
    {
        isQuestionConcerned=true;
        concernQuestionButton->setText("取消关注问题");
    }
    else
    {
        isQuestionConcerned=false;
        concernQuestionButton->setText("关注问题");
    }
}

void QuestionTitleAndDetail::clearInfo()
{
    this->setStyleSheet("background-color: rgba(90,90,90,0)");
    titleLabel->clear();
    detailLabel->clear();
    dateTimeLabel->clear();
    userNameLabel->clear();
    answerAmountLabel->clear();

    sortButton->setText("");
    sortButton->setEnabled(false);
    sortButton->setStyleSheet("border-width: 0px");
    intoDetailButton->setText("");
    intoDetailButton->setEnabled(false);
    intoDetailButton->setStyleSheet("border-width: 0px");
    concernUserButton->setText("");
    concernUserButton->setEnabled(false);
    concernUserButton->setStyleSheet("border-width: 0px");
    concernQuestionButton->setText("");
    concernQuestionButton->setEnabled(false);
    concernQuestionButton->setStyleSheet("border-width: 0px");
    addOrChangeAnswerButton->setText("");
    addOrChangeAnswerButton->setEnabled(false);
    addOrChangeAnswerButton->setStyleSheet("border-width: 0px");
}

void QuestionTitleAndDetail::setMode(const int &mode)
{
    switch(mode)
    {
        case 0:
        {
            sortButton->setHidden(false);
            intoDetailButton->setHidden(true);
            addOrChangeAnswerButton->setHidden(false);
            currentUserAnswerID=Overall::mainWindow->getUserAnswerQuestionID(Overall::currentUserID,questionID);
            if(currentUserAnswerID==-1)
                addOrChangeAnswerButton->setText("我来回答");
            else
                addOrChangeAnswerButton->setText("编辑回答");
            connect(addOrChangeAnswerButton,SIGNAL(clicked()),this,SLOT(onAddOrChangeAnswerButtonClicked()));
            connect(this,SIGNAL(addOrChangeAnswerSignal(int,int)),Overall::mainWindow,SLOT(onAddAnswerButtonClicked(int,int)));
            break;
        }
        case 1:
        {
            sortButton->setHidden(true);
            intoDetailButton->setHidden(false);
            addOrChangeAnswerButton->setHidden(true);
            break;
        }
        default:
            break;
    }
}

void QuestionTitleAndDetail::onSortButtonClicked()
{
    if(sortButton->text()=="点击按时间排序")
    {
        sortButton->setText("点击按赞数排序");
        emit sortSignal(0);
    }
    else if(sortButton->text()=="点击按赞数排序")
    {
        sortButton->setText("点击按时间排序");
        emit sortSignal(1);
    }
}

void QuestionTitleAndDetail::onIntoDetailButtonClicked()
{
    emit showQuestionSignal(questionID);
}

void QuestionTitleAndDetail::onConcernUserButtonClicked()
{
    if(isAuthorConcerned)
    {
        isAuthorConcerned=false;
        concernUserButton->setText("关注提问者");
        Overall::mainWindow->deleteAconcerningB(Overall::currentUserID,userID);
    }
    else
    {
        isAuthorConcerned=true;
        concernUserButton->setText("取消关注提问者");
        Overall::mainWindow->addAconcerningB(Overall::currentUserID,userID);
    }
    emit concernStateChanged(userID);
}

void QuestionTitleAndDetail::onConcernQuestionButtonClicked()
{
    if(isQuestionConcerned)
    {
        isQuestionConcerned=false;
        concernQuestionButton->setText("关注问题");
        Overall::mainWindow->deleteConcerningQuestion(Overall::currentUserID,questionID);
    }
    else
    {
        isQuestionConcerned=true;
        concernQuestionButton->setText("取消关注问题");
        Overall::mainWindow->addConcerningQuestion(Overall::currentUserID,questionID);
    }
}

void QuestionTitleAndDetail::onAddOrChangeAnswerButtonClicked()
{
    emit addOrChangeAnswerSignal(Overall::currentUserID,questionID);
}

int QuestionTitleAndDetail::getUserID()
{
    return userID;
}

void QuestionTitleAndDetail::updateConcernOrNotButton()
{
    if(Overall::mainWindow->checkISAconcerningB(Overall::currentUserID,userID))
    {
        isAuthorConcerned=true;
        concernUserButton->setText("取消关注提问者");
    }
    else
    {
        isAuthorConcerned=false;
        concernUserButton->setText("关注提问者");
    }
}

QuestionTitleAndDetail::~QuestionTitleAndDetail()
{
    delete titleLabel;
    delete detailLabel;
    delete userNameLabel;
    delete dateTimeLabel;
    delete answerAmountLabel;
    delete addOrChangeAnswerButton;
    delete intoDetailButton;
    delete concernUserButton;
    delete concernQuestionButton;
    delete sortButton;
    delete buttonLayout;
    delete infoLayout;
    delete mainLayout;
}
