#ifndef EDITPERSONINFORMATION
#define EDITPERSONINFORMATION
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QFrame>
#include <QShowEvent>
#include <QPushButton>
#include <QFileDialog>
#include "overall.h"
#include "user.h"

class User;
class EditPersonalInformation:public QFrame
{
    Q_OBJECT
    public:
        EditPersonalInformation(QWidget *parent=0);
        EditPersonalInformation(const int &userID,const int &mode=0,QWidget *parent=0);
        ~EditPersonalInformation();
    private:
        QLabel *userNameLabel,*introductionLabel,*genderLabel,*birthdayLabel,*avatarLabel,*statisticLabel;
        QLineEdit *userNameEdit;
        QTextEdit *introductionEdit;
        QDateEdit *birthdayEdit;
        QCalendarWidget *calendar;
        QRadioButton *radioButtonMale,*radioButtonFemale,*radioButtonUnknown;
        QPushButton *changeAvatarButton,*saveButton;
        QHBoxLayout *userNameLayout,*birthdayLayout,*genderLayout,*subHorizontalLayout;
        QVBoxLayout *vLayout,*avatarLayout,*mainLayout;
        void showEvent(QShowEvent *e);
        QString avatarPath;
        bool avatarChanged;
        class User *rec;
    private slots:
        void onSaveButtonClicked();
        void onChangeAvatarButtonClicked();
    signals:
        void userInfoUpdated(class User tmpUser);
        void avatarChangedSignal();
};

#endif // EDITPERSONINFORMATION

