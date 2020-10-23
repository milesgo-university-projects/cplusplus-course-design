#ifndef BASICINFO
#define BASICINFO
#include <QDateTime>

class BasicInfo
{//回答、提问信息的抽象类
    protected:
        int infoID;
        int userID;//回答者、提问者
        QDateTime dateTime;//创建日期
        QString content;//内容
    public:
        int getInfoID();
        int getUserID();
        QDateTime getDateTime();
        QString getContent();

        void setInfoID(const int &infoID);
        void setUserID(const int &userID);
        void setDateTime(const QDateTime &dateTime);
        void setContent(const QString &content);
        virtual void readInfo() = 0;
        virtual void writeInfo() = 0;
};

#endif // BASICINFO

