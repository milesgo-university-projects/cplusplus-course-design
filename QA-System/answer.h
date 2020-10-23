#ifndef ANSWER
#define ANSWER
#include "basicinfo.h"
#include <QSet>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "overall.h"
#include "functions.h"

class Answer:public BasicInfo
{
    public:
        Answer();
        Answer(const int &infoID,const int &userID,const QDateTime &dateTime,const QString &content);
        ~Answer();
    private:
        QSet<int> praisers;
    public:
        static QMap<int,int> answerIDToQuestionID;
        static QMap<int,int> answerIDToUserID;
        static void readAnswerIDToQuestionID();
        static void readAnswerIDToUserID();
        static void writeAnswerIDToQuestionID();
        static void writeAnswerIDToUserID();
        int getPraiseNum();
        bool isPraisedBy(const int &userID);
        void addPraiser(const int &userID);
        void deletePraiser(const int &userID);
        QSet<int> getPraisers();
        void clearPraisers();
        virtual void readInfo();
        virtual void writeInfo();
        friend QTextStream& operator <<(QTextStream& out,Answer answer);
        friend QTextStream& operator >>(QTextStream& in,Answer &answer);
};

#endif // ANSWER

