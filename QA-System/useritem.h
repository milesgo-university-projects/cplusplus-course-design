#ifndef USERITEM
#define USERITEM
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <user.h>

class UserItem:public QFrame
{
    Q_OBJECT
    public:
        UserItem(QWidget *parent=0);
        UserItem(class User tmpUser,QWidget *parent=0);
        ~UserItem();
        void changeInfo(class User tmpUser);
        void hideInfo();
        void showInfo();
        void setConcernOrNotButtonText(QString info);
        void setConcernOrNotButtonHidden(bool flag);
        void setLookingDetailButtonHidden(bool flag);
    private:
        QLabel *avatarLabel,*userNameLabel,*statisticLabel;
        QVBoxLayout *infoLayout;
        QHBoxLayout *mainLayout;
        QPushButton *concernOrNotButton,*lookingDetailButton;
        int userID;
    private slots:
        void onConcernOrNotButtonClicked();
        void onLookingDetailButtonClicked();
    signals:
        void concernState(int UserID,bool flag);
};

#endif // USERITEM

