#ifndef GUIDEZONE
#define GUIDEZONE
#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include <QShowEvent>
#include "simplebutton.h"
#include "dividewidget.h"
#include "overall.h"

class GuideZone:public QWidget
{
    Q_OBJECT
    public:
        GuideZone(const int &mode=0,QWidget *parent=0);
        ~GuideZone();
        SimpleButton *allQuestions,*allMyQuetions,*allMyAnswers,*allMyConcernedQuestions,*allMyConcernedUsers,*allMyFollowers;
        SimpleButton *editPersonalInfo,*addQuestionButton;
        SimpleButton *signOutButton;
        void setMode(const int &mode);//mode=0表示自己的信息导航，mode=1表示他人的信息导航
        int getMode();
    private:
        int mode;
        QVector<DivideWidget*> divideWidgets;
        QVBoxLayout *mainLayout;
        QLabel *avatarPix,*userNameLabel;
        void showEvent(QShowEvent *e);
    public slots:
        void updateAvatarInfo();
};

#endif // GUIDEZONE

