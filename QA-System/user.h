#ifndef USER
#define USER
#include <QMap>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QVector>
#include <QSet>
#include "overall.h"
#include "functions.h"

class User
{
    private:
        QString userName;//用户名
        int userID;//用户标识符，对用户不可见
        QDate birthday;//生日
        int gender;//性别,0表示男，1表示女，2表示未知
        QString introduction;//个人介绍

        QSet<int> fans;//粉丝ID
        QSet<int> concernUsers;//关注用户ID
        QSet<int> concernQuetions;
        QSet<int> myQuestions;
        QSet<int> myAnswers;
    public:
        QString getUserName();
        int getUserID();
        QDate getBirthday();
        int getGender();
        QString getIntroduction();
        int getPraiseNum();

        void setUserName(const QString &userName);
        void setUserID(const int &userID);
        void setBirthday(const QDate &birthday);
        void setGender(const int &gender);
        void setIntroduction(const QString &introduction);

        void clearFans();
        void clearConcernUsers();
        void clearConcernQuestions();
        void clearMyQuestions();
        void clearMyAnswers();
        void addFans(int userID);
        void deleteFans(int userID);
        void addConcernUsers(int userID);
        void deleteConcernUsers(int userID);
        void addConcernQuetions(int questionID);
        void deleteConcernQuestions(int questionID);
        void addMyQuestions(int questionID);
        void addMyAnswers(int answerID);
        QSet<int> getFans();
        QSet<int> getconcernUsers();
        QSet<int> getConcernQuetions();
        QSet<int> getMyQuestions();
        QSet<int> getMyAnswers();
        int getFansSize();
        int getconcernUsersSize();
        int getConcernQuetionsSize();
        int getMyQuestionsSize();
        int getMyAnswersSize();
        bool isConcernedBy(const int &userID);
        bool isConcerningQuestion(const int &questionID);
        int getAnswerID(const int &qustionID);
    public:
        static QMap<QString,int> userNameToID;
        static QMap<int,QString> IDToUserName;
        static QMap<int,QString> userIDToPassword;
        static void readUserNameToID();
        static void writeUserNameToID();
        static void readUserIDToPassword();
        static void writeUserIDToPassword();
        static bool checkUserPassword(const QString &userName,const QString &password);
        friend QTextStream& operator <<(QTextStream& out,User user);
        friend QTextStream& operator >>(QTextStream& in,User &user);
};

#endif // USER

