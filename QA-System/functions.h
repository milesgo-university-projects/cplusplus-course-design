#ifndef FUNCTIONS
#define FUNCTIONS
#include <QString>
#include <QByteArray>
#include <QCryptographicHash>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QTextStream>
#include "overall.h"
#include "user.h"

class User;
class Answer;
class Question;
namespace Function
{
    QString md5(const QString &str);
    void setStyle(const QString &style);
    QPixmap PixmapToRound(const QPixmap &src, const int &radius);//将图片形状变为圆形
    bool compareAnswerAccordingToDateTime(int a,int b);
    bool compareAnswerAccordingToPraiseNum(int a,int b);
    bool compareQuestionAccordingToDateTime(int a,int b);
    QTextStream& operator <<(QTextStream& out,User user);
    QTextStream& operator >>(QTextStream& in,User &user);
    QTextStream& operator <<(QTextStream& out,Answer answer);
    QTextStream& operator >>(QTextStream& in,Answer &answer);
    QTextStream& operator <<(QTextStream& out,Question question);
    QTextStream& operator >>(QTextStream& in,Question &question);
}

#endif // FUNCTIONS

