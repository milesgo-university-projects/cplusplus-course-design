#ifndef OVERALL
#define OVERALL
#include <QMap>
#include <QStack>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QSettings>
#include <QWidget>
#include <QObject>
#include <QApplication>
#include "user.h"
#include "answer.h"
#include "loginwidget.h"
#include "mainwindow.h"
#include "question.h"
class loginDialog;
class MainWindow;

namespace Overall
{//变量必须设置为声明，定义在对应的CPP文件中，否则会产生重复定义的问题
    extern QStack<int> windowStack;
    extern QMap<int,int> stackLocationToID;
    extern QStack<QDateTime> startDateTimeStack;
    extern QStack<QDateTime> endDateTimeStack;
    extern QStack<QString> contentStack;
    extern QMap<int,int> stackLocationToMineOrHis;//0表示我的导航栏，1表示查看他人信息的导航栏
    extern bool windowControl;//true表示是正常点击产生的，false表示是回退产生的
    extern int currentLookingUserID;
    extern int currentUserID;
    extern QString currentUserName;
    extern int userIDCnt;
    extern int answerIDCnt;
    extern int questionIDCnt;
    extern QSettings *settings;
    extern MainWindow *mainWindow;
    extern loginDialog *login;
    extern int qustionCnt,questionAmount;
    extern int userReadWriteFlag;//由于信息分别存放在不同的文件夹中，所以用一个全局变量表示现在应该读什么信息，方便重载输入输出
    extern int answerReadWriteFlag;
    extern int questionReadWriteFlag;
    void init();
}
#endif // OVERALL

