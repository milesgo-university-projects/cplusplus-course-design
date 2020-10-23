#ifndef USERLISTWIDGET
#define USERLISTWIDGET
#include <QWidget>
#include <QFrame>
#include <QList>
#include <QVector>
#include <QMap>
#include "user.h"
#include "useritem.h"
#include "pagelistwidget.h"
class UserItem;

class UserListWidget:public PageListWidget
{
    Q_OBJECT
    public:
        UserListWidget(QWidget *parent=0);
        UserListWidget(const int &mode=0,const int &userID=0,QWidget *parent=0);
        ~UserListWidget();
    private:
        QList<UserItem *> userItemList;
        virtual void setItems(int ll,int rr,int bound) override;
    private slots:
        void onConcernStateChanged(int userID,bool flag);
};

#endif // USERLISTWIDGET

