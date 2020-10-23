#include "question.h"
QMap<int,int> Question::questionIDToUserID;

Question::Question()
{

}

Question::Question(const int &infoID, const int &userID, const QDateTime &dateTime, const QString &content, const QString &title)
{
    this->infoID=infoID;
    this->userID=userID;
    this->dateTime=dateTime;
    this->content=content;
    this->title=title;
}

Question::~Question()
{

}

QSet<int> Question::getAnswerSet()
{
    return answerSet;
}

void Question::deleteAnswer(const int &answerID)
{
    answerSet.remove(answerID);
}

void Question::addAnswer(const int &answerID)
{
    answerSet.insert(answerID);
}

QString Question::getTitle()
{
    return title;
}

void Question::setTitle(const QString &title)
{
    this->title=title;
}

void Question::readQuestionIDToUserID()
{//未测试
    questionIDToUserID.clear();
    QFile file("../data/questionBelongToUser.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in answer.cpp";
    }
    QTextStream in(&file);
    int questionID,userID;
    while(!in.atEnd())
    {
        in>>questionID>>userID;
        questionIDToUserID[questionID]=userID;
    }
    file.close();
}

void Question::writeQuestionIDToUserID()
{
    QFile file("../data/questionBelongToUser.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in answer.cpp";
    }
    QTextStream out(&file);
    for(QMap<int,int>::iterator it=questionIDToUserID.begin();it!=questionIDToUserID.end();it++)
    {
        out<<it.key()<<" "<<it.value()<<"\n";
    }
    file.close();
}

void Question::clearAnswer()
{
    answerSet.clear();
}

void Question::readInfo()
{
    QFile file;
    int year,month,day,hour,minute,second;

    file.setFileName("../data/questions/answerList/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 19";
    }
    answerSet.clear();
    QTextStream in1(&file);
    int amount,ID;
    in1>>amount;
    for(int i=0;i<amount;i++)
    {
        in1>>ID;
        answerSet.insert(ID);
    }
    file.close();

    file.setFileName("../data/questions/title/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 20";
    }
    title=QTextStream(&file).readAll();
    file.close();

    file.setFileName("../data/questions/detail/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 21";
    }
    content=QTextStream(&file).readAll();
    file.close();

    file.setFileName("../data/questions/information/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 22";
    }
    QTextStream in2(&file);
    year=2000,month=1,day=1,hour=12,minute=0,second=0;
    if(!in2.atEnd())//waiting for you
        in2>>year>>month>>day>>hour>>minute>>second;
    dateTime=QDateTime(QDate(year,month,day),QTime(hour,minute,second));
    file.close();
}

void Question::writeInfo()
{
    QFile file;

    file.setFileName("../data/questions/answerList/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 23";
    }
    QTextStream out1(&file);
    out1<<answerSet.size()<<"\n";
    for(QSet<int>::iterator it=answerSet.begin();it!=answerSet.end();it++)
    {
        out1<<*it<<" ";
    }
    out1<<"\n";
    file.close();

    file.setFileName("../data/questions/title/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 24";
    }
    QTextStream out2(&file);
    out2<<title;
    file.close();

    file.setFileName("../data/questions/detail/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 25";
    }
    QTextStream out3(&file);
    out3<<content;
    file.close();

    file.setFileName("../data/questions/information/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 26";
    }
    QTextStream out4(&file);
    out4<<dateTime.date().year()<<" "<<dateTime.date().month()<<" "<<dateTime.date().day()<<" "<<dateTime.time().hour()<<" "<<dateTime.time().minute()<<" "<<dateTime.time().second();
    file.close();
}
