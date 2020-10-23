#include "functions.h"

QTextStream& operator <<(QTextStream& out,User user)
{
    int flag=Overall::userReadWriteFlag;
    if(flag==0)
    {//写入性别、生日、被赞次数等信息
        QDate date=user.getBirthday();
        out<<user.getGender()<<" "<<date.year()<<" "<<date.month()<<" "<<date.day();
    }
    else if(flag==1)
    {//写入个人简介
        out<<user.getIntroduction();
    }
    else if(flag==2)
    {//写入读者的回答信息
        QSet<int> myAnswers=user.getMyAnswers();
        out<<myAnswers.size()<<"\n";
        for(QSet<int>::iterator it=myAnswers.begin();it!=myAnswers.end();it++)
        {
            out<<*it<<" ";
        }
    }
    else if(flag==3)
    {//写入读者的粉丝信息
        QSet<int> fans=user.getFans();
        out<<fans.size()<<"\n";
        for(QSet<int>::iterator it=fans.begin();it!=fans.end();it++)
        {
            out<<*it<<" ";
        }
    }
    else if(flag==4)
    {//写入读者的关注用户信息
        QSet<int> concernUsers=user.getconcernUsers();
        out<<concernUsers.size()<<"\n";
        for(QSet<int>::iterator it=concernUsers.begin();it!=concernUsers.end();it++)
        {
            out<<*it<<" ";
        }
    }
    else if(flag==5)
    {//写入读者的提问信息
        QSet<int> myQuestions=user.getMyQuestions();
        out<<myQuestions.size()<<"\n";
        for(QSet<int>::iterator it=myQuestions.begin();it!=myQuestions.end();it++)
        {
            out<<*it<<" ";
        }
    }
    else if(flag==6)
    {//写入读者的关注提问信息
        QSet<int> concernQuestions=user.getConcernQuetions();
        out<<concernQuestions.size()<<"\n";
        for(QSet<int>::iterator it=concernQuestions.begin();it!=concernQuestions.end();it++)
        {
            out<<*it<<" ";
        }
    }
    return out;
}

QTextStream& operator >>(QTextStream& in,User &user)
{
    int flag=Overall::userReadWriteFlag;
    if(flag==0)
    {//读入性别、生日、被赞次数等信息
        int gender,year,month,day;
        if(in.atEnd())
        {
            gender=2;year=2000;month=1;day=1;;
        }
        else
        {
            in>>gender>>year>>month>>day;
        }
        user.setGender(gender);
        user.setBirthday(QDate(year,month,day));
    }
    else if(flag==1)
    {//读入个人简介
        QString introduction="";
        if(!in.atEnd())
        {
            introduction=in.readAll();
        }
        user.setIntroduction(introduction);
    }
    else if(flag==2)
    {//读入读者的回答信息
        int amount,answerID;
        user.clearMyAnswers();
        if(!in.atEnd())
        {
            in>>amount;
            for(int i=0;i<amount;i++)
            {
                in>>answerID;
                user.addMyAnswers(answerID);
            }
        }
    }
    else if(flag==3)
    {//读入读者的粉丝信息
        int amount,userID;
        user.clearFans();
        if(!in.atEnd())
        {
            in>>amount;
            for(int i=0;i<amount;i++)
            {
                in>>userID;
                user.addFans(userID);
            }
        }
    }
    else if(flag==4)
    {//读入读者的关注用户信息
        int amount,userID;
        user.clearConcernUsers();
        if(!in.atEnd())
        {
            in>>amount;
            for(int i=0;i<amount;i++)
            {
                in>>userID;
                user.addConcernUsers(userID);
            }
        }
    }
    else if(flag==5)
    {//读入读者的提问信息
        int amount,questionID;
        user.clearMyQuestions();
        if(!in.atEnd())
        {
            in>>amount;
            for(int i=0;i<amount;i++)
            {
                in>>questionID;
                user.addMyQuestions(questionID);
            }
        }
    }
    else if(flag==6)
    {//读入读者的关注提问信息
        int amount,questionID;
        user.clearConcernQuestions();
        if(!in.atEnd())
        {
            in>>amount;
            for(int i=0;i<amount;i++)
            {
                in>>questionID;
                user.addConcernQuetions(questionID);
            }
        }
    }
    return in;
}

QTextStream& operator <<(QTextStream& out,Answer answer)
{
    int flag=Overall::answerReadWriteFlag;
    if(flag==0)
    {//日期
        QDateTime dateTime=answer.getDateTime();
        out<<dateTime.date().year()<<" "<<dateTime.date().month()<<" "<<dateTime.date().day()<<" "<<dateTime.time().hour()<<" "<<dateTime.time().minute()<<" "<<dateTime.time().second();
    }
    else if(flag==1)
    {//内容
        out<<answer.getContent();
    }
    else if(flag==2)
    {//点赞者
        out<<answer.getPraiseNum()<<"\n";
        QSet<int> praisers=answer.getPraisers();
        for(QSet<int>::iterator it=praisers.begin();it!=praisers.end();it++)
        {
            out<<*it<<" ";
        }
    }
    return out;
}

QTextStream& operator >>(QTextStream& in,Answer &answer)
{
    int flag=Overall::answerReadWriteFlag;
    if(flag==0)
    {//日期
        int year,month,day,hour,second,minute;
        if(!in.atEnd())
        {
            year=2000;month=1;day=1;hour=12;second=0;minute=0;
        }
        else
        {
            in>>year>>month>>day>>hour>>second>>minute;
        }
        answer.setDateTime(QDateTime(QDate(year,month,day),QTime(hour,second,minute)));
    }
    else if(flag==1)
    {//内容
        QString content="";
        if(!in.atEnd())
            content=in.readAll();
        answer.setContent(content);
    }
    else if(flag==2)
    {//点赞者
        int amount,userID;
        answer.clearPraisers();
        if(!in.atEnd())
        {
            in>>amount;
            for(int i=0;i<amount;i++)
            {
                in>>userID;
                answer.addPraiser(userID);
            }
        }
    }
    return in;
}

QTextStream& operator <<(QTextStream& out,Question question)
{
    int flag=Overall::questionReadWriteFlag;
    if(flag==0)
    {//回答
        QSet<int> answerSet=question.getAnswerSet();
        out<<answerSet.size()<<"\n";
        for(QSet<int>::iterator it=answerSet.begin();it!=answerSet.end();it++)
        {
            out<<*it<<" ";
        }
    }
    else if(flag==1)
    {//标题
        out<<question.getTitle();
    }
    else if(flag==2)
    {//详细描述
        out<<question.getContent();
    }
    else if(flag==3)
    {//日期
        QDateTime dateTime=question.getDateTime();
        out<<dateTime.date().year()<<" "<<dateTime.date().month()<<" "<<dateTime.date().day()<<" "<<dateTime.time().hour()<<" "<<dateTime.time().minute()<<" "<<dateTime.time().second();
    }
    return out;
}

QTextStream& operator >>(QTextStream& in,Question &question)
{
    int flag=Overall::questionReadWriteFlag;
    if(flag==0)
    {//回答
        int amount,answerID;
        question.clearAnswer();
        if(!in.atEnd())
        {
            in>>amount;
            for(int i=0;i<amount;i++)
            {
                in>>answerID;
                question.addAnswer(answerID);
            }
        }
    }
    else if(flag==1)
    {//标题
        QString title="";
        if(!in.atEnd())
            title=in.readAll();
        question.setTitle(title);
    }
    else if(flag==2)
    {//详细描述
        QString content="";
        if(!in.atEnd())
            content=in.readAll();
        question.setContent(content);
    }
    else if(flag==3)
    {//日期
        int year,month,day,hour,minute,second;
        if(in.atEnd())
        {
            year=2000;month=1;day=1;hour=12;minute=0;second=0;
        }
        else
        {
            in>>year>>month>>day>>hour>>minute>>second;
        }
        question.setDateTime(QDateTime(QDate(year,month,day),QTime(hour,minute,second)));
    }
    return in;
}

QString Function::md5(const QString &str)
{
    QByteArray bb;
    bb = QCryptographicHash::hash (str.toLatin1(), QCryptographicHash::Md5);
    return bb.toHex();
}

void Function::setStyle(const QString &style)
{
    QFile qss(style);
    if(!qss.open(QFile::ReadOnly))
    {
        qDebug()<<"open file error in functions.cpp file location: "<<style;
    }
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

QPixmap Function::PixmapToRound(const QPixmap &src, const int &radius)
{
    if(src.isNull())
    {
        return QPixmap();
    }
    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);

    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}

bool Function::compareAnswerAccordingToDateTime(int a, int b)
{
    QDateTime dateTimeA=Overall::mainWindow->getAnswerDateTime(a);
    QDateTime dateTimeB=Overall::mainWindow->getAnswerDateTime(b);
    return dateTimeA>dateTimeB;
}

bool Function::compareAnswerAccordingToPraiseNum(int a, int b)
{
    int praiseNumA=Overall::mainWindow->getAnswerPraiseNum(a);
    int praiseNumB=Overall::mainWindow->getAnswerPraiseNum(b);
    return praiseNumA>praiseNumB;
}

bool Function::compareQuestionAccordingToDateTime(int a, int b)
{
    QDateTime dateTimeA=Overall::mainWindow->getQuestionDateTime(a);
    QDateTime dateTimeB=Overall::mainWindow->getQuestionDateTime(b);
    return dateTimeA>dateTimeB;
}
