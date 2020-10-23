#include "addanswerpage.h"
//cpp文件共3709行
AddAnswerPage::AddAnswerPage(int userID,int questionID,QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    cancelButton = new QPushButton;
    cancelButton->setText("取消");
    cancelButton->setFocusPolicy(Qt::NoFocus);
    submitButton = new QPushButton;
    submitButton->setText("提交");
    submitButton->setFocusPolicy(Qt::NoFocus);
    textEdit = new SizeLimitedTextEdit(10000);
    textEdit->setPlaceholderText("请输入回答（限10000字）");

    buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(5);
    buttonLayout->addWidget(cancelButton,2);
    buttonLayout->addStretch(3);
    buttonLayout->addWidget(submitButton,2);
    buttonLayout->addStretch(5);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(textEdit,50);
    mainLayout->addLayout(buttonLayout,1);

    setLayout(mainLayout);

    answerID=Overall::mainWindow->getUserAnswerQuestionID(userID,questionID);
    this->questionID=questionID;
    if(answerID!=-1)
        textEdit->setText(Overall::mainWindow->getAnswerContent(answerID));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(onCancelButtonClicked()));
    connect(submitButton,SIGNAL(clicked()),this,SLOT(onSubmitButtonClicked()));
}

AddAnswerPage::~AddAnswerPage()
{
    delete cancelButton;
    delete submitButton;
    delete textEdit;
    delete buttonLayout;
    delete mainLayout;
}

void AddAnswerPage::showEvent(QShowEvent *e)
{
    if(Overall::windowControl)
    {
        int loc=Overall::windowStack.size();
        Overall::windowStack.push(10);
        Overall::stackLocationToID[loc]=questionID;
    }
    QWidget::showEvent(e);
}

void AddAnswerPage::onCancelButtonClicked()
{
    this->close();
    Overall::mainWindow->onRetreatButtonClicked();
}

void AddAnswerPage::onSubmitButtonClicked()
{//提交新编辑的回答
    if(textEdit->toPlainText().trimmed()=="")
    {
        QMessageBox message(QMessageBox::Warning,"警告","回答不能为空！",QMessageBox::Yes,NULL);
        message.setButtonText(QMessageBox::Yes,"好的");
        message.exec();
        return;
    }
    if(answerID==-1)
    {
        answerID=Overall::answerIDCnt++;
        Overall::settings->setValue("answerIDCnt",Overall::answerIDCnt);
    }
    Overall::mainWindow->addAnswerOfUser(answerID,Overall::currentUserID);
    Overall::mainWindow->addAnswerOfQuestion(answerID,questionID);
    Answer::answerIDToQuestionID[answerID]=questionID;
    Answer::answerIDToUserID[answerID]=Overall::currentUserID;
    Overall::mainWindow->answerIDToAnswerObject[answerID]=Answer(answerID,Overall::currentUserID,QDateTime::currentDateTime(),textEdit->toPlainText());
    Overall::mainWindow->onRetreatButtonClicked();
}
