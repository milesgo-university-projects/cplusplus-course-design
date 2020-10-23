#ifndef QUESTION
#define QUESTION
#include "basicinfo.h"
#include <QSet>
#include <QMap>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "overall.h"
#include "functions.h"

class Question:public BasicInfo
{
    public:
        Question();
        Question(const int &infoID,const int &userID,const QDateTime &dateTime,const QString &content,const QString &title);
        ~Question();
    private:
        QSet<int> answerSet;
        QString title;
    public:
        QSet<int> getAnswerSet();
        void deleteAnswer(const int &answerID);
        void addAnswer(const int &answerID);
        void clearAnswer();
        QString getTitle();
        void setTitle(const QString &title);
    public:
        static QMap<int,int> questionIDToUserID;
        static void readQuestionIDToUserID();
        static void writeQuestionIDToUserID();
        virtual void readInfo();
        virtual void writeInfo();
        friend QTextStream& operator <<(QTextStream& out,Question question);
        friend QTextStream& operator >>(QTextStream& in,Question &question);
};

#endif // QUESTION

