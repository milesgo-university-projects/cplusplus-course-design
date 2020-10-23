#include "basicinfo.h"

int BasicInfo::getInfoID()
{
    return infoID;
}

int BasicInfo::getUserID()
{
    return userID;
}

QDateTime BasicInfo::getDateTime()
{
    return dateTime;
}

QString BasicInfo::getContent()
{
    return content;
}



void BasicInfo::setInfoID(const int &infoID)
{
    this->infoID=infoID;
}

void BasicInfo::setUserID(const int &userID)
{
    this->userID=userID;
}

void BasicInfo::setDateTime(const QDateTime &dateTime)
{
    this->dateTime=dateTime;
}

void BasicInfo::setContent(const QString &content)
{
    this->content=content;
}
