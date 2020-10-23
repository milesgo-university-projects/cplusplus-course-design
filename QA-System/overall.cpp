#include "overall.h"

int Overall::currentLookingUserID;
int Overall::currentUserID;
int Overall::userIDCnt;
int Overall::answerIDCnt;
int Overall::questionIDCnt;
int Overall::qustionCnt,Overall::questionAmount;
int Overall::userReadWriteFlag;
int Overall::answerReadWriteFlag;
int Overall::questionReadWriteFlag;
bool Overall::windowControl;
QStack<int> Overall::windowStack;
QMap<int,int> Overall::stackLocationToID;
QStack<QDateTime> Overall::startDateTimeStack;
QStack<QDateTime> Overall::endDateTimeStack;
QStack<QString> Overall::contentStack;
QMap<int,int> Overall::stackLocationToMineOrHis;
QString Overall::currentUserName;
QSettings* Overall::settings = new QSettings("../option/settings.ini",QSettings::IniFormat);
MainWindow* Overall::mainWindow;
loginDialog* Overall::login;

void Overall::init()
{
    windowStack.clear();
    stackLocationToID.clear();
    User::readUserNameToID();//读取用户名和ID的映射
    User::readUserIDToPassword();//读取ID和密码的映射
    Answer::readAnswerIDToQuestionID();//读取答案ID和问题ID的映射
    Answer::readAnswerIDToUserID();//读取答案ID和回答者ID的映射
    Question::readQuestionIDToUserID();//读取问题和提问者ID的映射
    userIDCnt=settings->value("userIDCnt",0).toInt();//读取用户ID计数值
    answerIDCnt=settings->value("answerIDCnt",0).toInt();
    questionIDCnt=settings->value("questionIDCnt",0).toInt();
    mainWindow=new MainWindow;
    login=new loginDialog;
    login->show();
    QObject::connect(login,SIGNAL(accepted()),mainWindow,SLOT(show()));
    QObject::connect(mainWindow,SIGNAL(loginAgain()),login,SLOT(show()));
}
