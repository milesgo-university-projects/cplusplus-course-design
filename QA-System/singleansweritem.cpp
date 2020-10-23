#include "singleansweritem.h"

SingleAnswerItem::SingleAnswerItem(QWidget *parent):QFrame(parent)
{
    contentLabel = new QLabel;
    contentLabel->setAttribute(Qt::WA_TranslucentBackground,true);
    contentLabel->adjustSize();
    contentLabel->setWordWrap(true);

    userNameLabel = new QLabel;
    userNameLabel->setAttribute(Qt::WA_TranslucentBackground,true);
    dateTimeLabel = new QLabel;
    dateTimeLabel->setAttribute(Qt::WA_TranslucentBackground,true);
    praiseNumLabel = new QLabel;
    praiseNumLabel->setAttribute(Qt::WA_TranslucentBackground,true);
    alreadyPraisedLabel = new QLabel;
    alreadyPraisedLabel->setAttribute(Qt::WA_TranslucentBackground,true);
    alreadyPraisedLabel->setFixedWidth(50);

    praiseButton = new twoSizeButton("praise_16px","praise_24px",QSize(30,30),QSize(16,16),QSize(24,24));

    concernUserButton = new QPushButton;
    concernUserButton->setFixedWidth(100);
    concernUserButton->setStyleSheet("background-color: transparent");
    concernUserButton->setFocusPolicy(Qt::NoFocus);

    infoLayout = new QHBoxLayout;
    infoLayout->addStretch(0);
    infoLayout->addWidget(praiseButton,0);
    infoLayout->addStretch(1);
    infoLayout->addWidget(alreadyPraisedLabel);
    infoLayout->addStretch(1);
    infoLayout->addWidget(concernUserButton);
    infoLayout->addStretch(20);
    infoLayout->addWidget(userNameLabel,3);
    infoLayout->addStretch(1);
    infoLayout->addWidget(dateTimeLabel,3);
    infoLayout->addStretch(1);
    infoLayout->addWidget(praiseNumLabel,3);
    infoLayout->addStretch(0);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(contentLabel);
    mainLayout->addLayout(infoLayout);

    setLayout(mainLayout);
    connect(praiseButton,SIGNAL(clicked()),this,SLOT(onPraiseButtonClicked()));
    connect(concernUserButton,SIGNAL(clicked()),this,SLOT(onConcernUserButtonClicked()));
}

void SingleAnswerItem::setAnswer(const int &answerID)
{
    this->answerID=answerID;
    this->setStyleSheet("background-color: rgba(111,111,111,100)");
    class Answer tmpAnswer=Overall::mainWindow->answerIDToAnswerObject[answerID];
    this->userID=tmpAnswer.getUserID();
    contentLabel->setText(tmpAnswer.getContent());
    userNameLabel->setText("回答者："+Overall::mainWindow->getUserName(tmpAnswer.getUserID()));
    QDateTime dateTime=tmpAnswer.getDateTime();
    QString dateTimeInfo=QString("时间：%1年%2月%3日%4时%5分").arg(dateTime.date().year()).arg(dateTime.date().month()).arg(dateTime.date().day()).arg(dateTime.time().hour()).arg(dateTime.time().minute());
    dateTimeLabel->setText(dateTimeInfo);
    praiseNum=tmpAnswer.getPraiseNum();
    praiseNumLabel->setText(QString("获赞：%1").arg(praiseNum));
    praiseButton->setHidden(false);
    concernUserButton->setHidden(false);

    if(Overall::mainWindow->isAnswerPraisedByUser(answerID,Overall::currentUserID))
        alreadyPraisedLabel->setText("您已点赞");
    else
        alreadyPraisedLabel->setText("");

    if(Overall::currentUserID==tmpAnswer.getUserID())
    {
        concernUserButton->setText("");
        concernUserButton->setStyleSheet("background-color: transparent;border-width: 0px");
    }
    else
    {
        if(Overall::mainWindow->checkISAconcerningB(Overall::currentUserID,tmpAnswer.getUserID()))
            concernUserButton->setText("取消关注回答者");
        else
            concernUserButton->setText("关注回答者");
        concernUserButton->setStyleSheet("background-color: transparent;border-width: 1px");
    }
}

void SingleAnswerItem::clearInfo()
{
    this->setStyleSheet("background-color: rgba(111,111,111,0)");
    contentLabel->clear();
    userNameLabel->clear();
    dateTimeLabel->clear();
    praiseNumLabel->clear();
    alreadyPraisedLabel->clear();
    praiseButton->setHidden(true);
    concernUserButton->setHidden(true);
}

void SingleAnswerItem::onPraiseButtonClicked()
{
    if(alreadyPraisedLabel->text()=="您已点赞")
    {
        alreadyPraisedLabel->setText("");
        praiseNum--;
        praiseNumLabel->setText(QString("获赞：%1").arg(praiseNum));
        Overall::mainWindow->deletePraiser(answerID,Overall::currentUserID);
    }
    else
    {
        alreadyPraisedLabel->setText("您已点赞");
        praiseNum++;
        praiseNumLabel->setText(QString("获赞：%1").arg(praiseNum));
        Overall::mainWindow->addPraiser(answerID,Overall::currentUserID);
    }
}

SingleAnswerItem::~SingleAnswerItem()
{
    delete contentLabel;
    delete userNameLabel;
    delete dateTimeLabel;
    delete praiseNumLabel;
    delete praiseButton;
    delete alreadyPraisedLabel;
    delete concernUserButton;
    delete infoLayout;
    delete mainLayout;
}

void SingleAnswerItem::onConcernUserButtonClicked()
{
    if(concernUserButton->text()=="关注回答者")
    {
        concernUserButton->setText("取消关注回答者");
        Overall::mainWindow->addAconcerningB(Overall::currentUserID,userID);
    }
    else
    {
        concernUserButton->setText("关注回答者");
        Overall::mainWindow->deleteAconcerningB(Overall::currentUserID,userID);
    }
    emit concernStateChanged(userID);
}

void SingleAnswerItem::updateConcernUserButton()
{
    if(Overall::mainWindow->checkISAconcerningB(Overall::currentUserID,userID))
        concernUserButton->setText("取消关注回答者");
    else
        concernUserButton->setText("关注回答者");
}

int SingleAnswerItem::getUserID()
{
    return userID;
}
