#include "answer.h"

QMap<int,int> Answer::answerIDToQuestionID;
QMap<int,int> Answer::answerIDToUserID;

Answer::Answer()
{

}

Answer::Answer(const int &infoID, const int &userID, const QDateTime &dateTime, const QString &content)
{
    this->infoID=infoID;
    this->userID=userID;
    this->dateTime=dateTime;
    this->content=content;
}

Answer::~Answer()
{

}

int Answer::getPraiseNum()
{
    return praisers.size();
}

void Answer::readAnswerIDToQuestionID()
{//未测试
    answerIDToQuestionID.clear();
    QFile file("../data/answerBelongToQuestion.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in answer.cpp";
    }
    QTextStream in(&file);
    int answerID,questionID;
    while(!in.atEnd())
    {
        in>>answerID>>questionID;
        answerIDToQuestionID[answerID]=questionID;
    }
    file.close();
}

void Answer::readAnswerIDToUserID()
{//未测试
    answerIDToUserID.clear();
    QFile file("../data/answerBelongToUser.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in answer.cpp";
    }
    QTextStream in(&file);
    int answerID,userID;
    while(!in.atEnd())
    {
        in>>answerID>>userID;
        answerIDToUserID[answerID]=userID;
    }
    file.close();
}

void Answer::writeAnswerIDToQuestionID()
{
    QFile file("../data/answerBelongToQuestion.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in answer.cpp";
    }
    QTextStream out(&file);
    for(QMap<int,int>::iterator it=answerIDToQuestionID.begin();it!=answerIDToQuestionID.end();it++)
    {
        out<<it.key()<<" "<<it.value()<<"\n";
    }
    file.close();
}

void Answer::writeAnswerIDToUserID()
{
    QFile file("../data/answerBelongToUser.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in answer.cpp";
    }
    QTextStream out(&file);
    for(QMap<int,int>::iterator it=answerIDToUserID.begin();it!=answerIDToUserID.end();it++)
    {
        out<<it.key()<<" "<<it.value()<<"\n";
    }
    file.close();
}

bool Answer::isPraisedBy(const int &userID)
{
    return praisers.contains(userID);
}

void Answer::addPraiser(const int &userID)
{
    praisers.insert(userID);
}

void Answer::deletePraiser(const int &userID)
{
    praisers.remove(userID);
}

QSet<int> Answer::getPraisers()
{
    return praisers;
}

void Answer::readInfo()
{
    QFile file;
    int year,month,day,hour,second,minute;

    file.setFileName("../data/answers/information/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error int mainwindow.cpp 13";
    }
    year=2000,month=1,day=1,hour=12,second=0,minute=0;
    QTextStream in1(&file);
    if(!in1.atEnd())//waiting for you
        in1>>year>>month>>day>>hour>>second>>minute;
    dateTime=QDateTime(QDate(year,month,day),QTime(hour,minute,second));
    file.close();

    file.setFileName("../data/answers/content/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 14";
    }
    content=QTextStream(&file).readAll();
    file.close();

    file.setFileName("../data/answers/praisers/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 15";
    }
    praisers.clear();
    QTextStream in2(&file);
    if(!in2.atEnd())
    {
        int amount,ID;
        in2>>amount;
        for(int i=0;i<amount;i++)
        {
            in2>>ID;
            praisers.insert(ID);
        }
    }
    file.close();
}

void Answer::writeInfo()
{
    QFile file;

    file.setFileName("../data/answers/information/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 16";
    }
    QTextStream out1(&file);
    out1<<dateTime.date().year()<<" "<<dateTime.date().month()<<" "<<dateTime.date().day()<<" "<<dateTime.time().hour()<<" "<<dateTime.time().minute()<<" "<<dateTime.time().second();
    file.close();

    file.setFileName("../data/answers/content/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 17";
    }
    QTextStream out2(&file);
    out2<<content;
    file.close();

    file.setFileName("../data/answers/praisers/"+QString("%1").arg(infoID)+".txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file error in mainwindow.cpp 18";
    }
    QTextStream out3(&file);
    out3<<praisers.size()<<"\n";
    for(QSet<int>::iterator it=praisers.begin();it!=praisers.end();it++)
    {
        out3<<*it<<" ";
    }
    file.close();
}

void Answer::clearPraisers()
{
    praisers.clear();
}
