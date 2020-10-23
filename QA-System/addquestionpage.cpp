#include "addquestionpage.h"

AddQuestionPage::AddQuestionPage(QWidget *parent):QWidget(parent)
{
    if(Overall::windowControl)
    {
        Overall::windowStack.push(11);
    }
    clearButton = new QPushButton;
    clearButton->setFocusPolicy(Qt::NoFocus);
    clearButton->setText("清空");
    submitButton = new QPushButton;
    submitButton->setFocusPolicy(Qt::NoFocus);
    submitButton->setText("提交");
    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(submitButton);

    titleEdit = new SizeLimitedTextEdit(200);
    titleEdit->setPlaceholderText("请输入提问标题（限200字）");
    detailEdit = new SizeLimitedTextEdit(3000);
    detailEdit->setPlaceholderText("请输入详细描述（限3000字）");

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleEdit,3);
    mainLayout->addWidget(detailEdit,50);
    mainLayout->addLayout(buttonLayout,1);

    setLayout(mainLayout);
    connect(clearButton,SIGNAL(clicked()),this,SLOT(onClearButtonClicked()));
    connect(submitButton,SIGNAL(clicked()),this,SLOT(onSubmitButtonClicked()));
    connect(this,SIGNAL(toAllQuestionFunctionZone()),Overall::mainWindow->guideZone->allQuestions,SLOT(click()));
}

AddQuestionPage::~AddQuestionPage()
{
    delete clearButton;
    delete submitButton;
    delete titleEdit;
    delete detailEdit;
    delete buttonLayout;
    delete mainLayout;
}

void AddQuestionPage::onClearButtonClicked()
{
    titleEdit->clear();
    detailEdit->clear();
}

void AddQuestionPage::onSubmitButtonClicked()
{
    if(titleEdit->toPlainText().trimmed()=="")
    {
        QMessageBox message(QMessageBox::Warning,"警告","标题不能为空！",QMessageBox::Yes,NULL);
        message.setButtonText(QMessageBox::Yes,"好的");
        message.exec();
        return;
    }
    int questionID=Overall::questionIDCnt++;
    Overall::settings->setValue("questionIDCnt",Overall::questionIDCnt);
    Overall::mainWindow->questionIDToQuestionObject[questionID]=Question(questionID,Overall::currentUserID,QDateTime::currentDateTime(),detailEdit->toPlainText(),titleEdit->toPlainText());
    Question::questionIDToUserID[questionID]=Overall::currentUserID;
    Overall::mainWindow->addQuestionOfUser(questionID,Overall::currentUserID);
    QMessageBox message(QMessageBox::Information,"恭喜","提交问题成功",QMessageBox::Yes,NULL);
    message.setButtonText(QMessageBox::Yes,"好的");
    message.exec();
    emit toAllQuestionFunctionZone();
}
