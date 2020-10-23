#include "user.h"

QString User::getUserName()
{
    return userName;
}

int User::getUserID()
{
    return userID;
}

QDate User::getBirthday()
{
    return birthday;
}

int User::getGender()
{
    return gender;
}

QString User::getIntroduction()
{
    return introduction;
}



void User::setUserName(const QString &userName)
{
    this->userName=userName;
}

void User::setUserID(const int &userID)
{
    this->userID=userID;
}

void User::setBirthday(const QDate &birthday)
{
    this->birthday=birthday;
}

void User::setGender(const int &gender)
{
    this->gender=gender;
}

void User::setIntroduction(const QString &introduction)
{
    this->introduction=introduction;
}

QMap<QString,int> User::userNameToID;//静态变量除了在类内声明，还需要在类外进行定义
QMap<int,QString> User::IDToUserName;

void User::readUserNameToID()
{
    QFile file("../data/user/nameToID.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in user.cpp file location: ../data/user/nameToID.txt";
    }
    QTextStream textStream(&file);
    QString name;
    int ID;
    userNameToID.clear();
    IDToUserName.clear();
    while(1)
    {
        textStream>>name>>ID;
        if(name=="")
            break;
        userNameToID[name]=ID;
        IDToUserName[ID]=name;
    }
    file.close();
}

void User::writeUserNameToID()
{
    QFile file("../data/user/nameToID.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in user.cpp file location: ../data/user/nameToID.txt";
    }
    QTextStream textStream(&file);
    for(QMap<QString,int>::iterator it=userNameToID.begin();it!=userNameToID.end();it++)
        textStream<<it.key()<<" "<<it.value()<<endl;
    file.close();
}

QMap<int,QString> User::userIDToPassword;

void User::readUserIDToPassword()
{
    QFile file("../option/ss.dat");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in user.cpp file location: ../option/ss.dat";
    }
    QTextStream textStream(&file);
    int ID;
    QString password;
    userIDToPassword.clear();
    while(1)
    {
        textStream>>ID>>password;
        if(password=="")
            break;
        userIDToPassword[ID]=password;
    }
    file.close();
}

void User::writeUserIDToPassword()
{
    QFile file("../option/ss.dat");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in user.cpp file location: ../option/ss.dat";
    }
    QTextStream textStream(&file);
    for(QMap<int,QString>::iterator it=userIDToPassword.begin();it!=userIDToPassword.end();it++)
        textStream<<it.key()<<" "<<it.value()<<endl;
    file.close();
}

bool User::checkUserPassword(const QString &userName,const QString &password)
{
    if(!userNameToID.contains(userName))
        return false;
    return userIDToPassword[userNameToID[userName]]==Function::md5(password);
}

void User::clearFans()
{
    fans.clear();
}

void User::clearConcernUsers()
{
    concernUsers.clear();
}

void User::clearConcernQuestions()
{
    concernQuetions.clear();
}

void User::clearMyQuestions()
{
    myQuestions.clear();
}

void User::clearMyAnswers()
{
    myAnswers.clear();
}

void User::addFans(int userID)
{
    fans.insert(userID);
}

void User::deleteFans(int userID)
{
    fans.remove(userID);
}

void User::addConcernUsers(int userID)
{
    concernUsers.insert(userID);
}

void User::deleteConcernUsers(int userID)
{
    concernUsers.remove(userID);
}

void User::addConcernQuetions(int questionID)
{
    concernQuetions.insert(questionID);
}

void User::deleteConcernQuestions(int questionID)
{
    concernQuetions.remove(questionID);
}

void User::addMyQuestions(int questionID)
{
    myQuestions.insert(questionID);
}

void User::addMyAnswers(int answerID)
{
    myAnswers.insert(answerID);
}

QSet<int> User::getFans()
{
    return fans;
}

QSet<int> User::getconcernUsers()
{
    return concernUsers;
}

QSet<int> User::getConcernQuetions()
{
    return concernQuetions;
}

QSet<int> User::getMyQuestions()
{
    return myQuestions;
}

QSet<int> User::getMyAnswers()
{
    return myAnswers;
}

int User::getFansSize()
{
    return fans.size();
}

int User::getconcernUsersSize()
{
    return concernUsers.size();
}

int User::getConcernQuetionsSize()
{
    return concernQuetions.size();
}

int User::getMyQuestionsSize()
{
    return myQuestions.size();
}

int User::getMyAnswersSize()
{
    return myAnswers.size();
}

int User::getPraiseNum()
{
    int praiseNum=0;
    for(QSet<int>::iterator it=myAnswers.begin();it!=myAnswers.end();it++)
    {
        praiseNum+=Overall::mainWindow->answerIDToAnswerObject[*it].getPraiseNum();
    }
    return praiseNum;
}

bool User::isConcernedBy(const int &userID)
{
    return fans.contains(userID);
}

bool User::isConcerningQuestion(const int &questionID)
{
    return concernQuetions.contains(questionID);
}

int User::getAnswerID(const int &questionID)
{
    int answerID=-1;
    for(QSet<int>::iterator it=myAnswers.begin();it!=myAnswers.end()&&answerID==-1;it++)
    {
        if(Answer::answerIDToQuestionID[*it]==questionID)
            answerID=*it;
    }
    return answerID;
}
