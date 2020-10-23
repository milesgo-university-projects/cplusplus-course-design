#ifndef MAINWINDOW
#define MAINWINDOW
#include <QWidget>
#include <QCloseEvent>
#include <QObject>
#include <QEvent>
#include <QVBoxLayout>
#include <QShowEvent>
#include <QString>
#include <qt_windows.h>
#include <windowsx.h>
#include "titlebar.h"
#include "guidezone.h"
#include "editpersoninformation.h"
#include "userlistwidget.h"
#include "questiondetailwidget.h"
#include "questionheadlinelist.h"
#include "myanswerlist.h"
#include "addanswerpage.h"
#include "addquestionpage.h"

class UserListWidget;
class GuideZone;
class EditPersonalInformation;
class QuestionHeadLineList;
class QuestionDetailWidget;
class MyAnswerList;
class titleBar;
class AddAnswerPage;
class AddQuestionPage;

class MainWindow:public QWidget
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent=0);
        ~MainWindow();
        QList<class User> userList;
        QMap<int,int> userIDToListLocation;
        QMap<int,class Answer> answerIDToAnswerObject;
        QMap<int,class Question> questionIDToQuestionObject;
        GuideZone *guideZone;

        bool checkISAconcerningB(const int &A,const int &B);
        void deleteAconcerningB(const int &A,const int &B);
        void addAconcerningB(const int &A,const int &B);
        void makeAconcernB(const int &A,const int &B,bool flag);
        QString getUserName(const int &userID);
        bool isAnswerPraisedByUser(const int &answerID,const int &userID);
        void addPraiser(const int &answerID,const int &userID);
        void deletePraiser(const int &answerID,const int &userID);
        bool isUserAconcerningQuestionB(const int &userID,const int questionID);
        void addConcerningQuestion(const int &userID,const int questionID);
        void deleteConcerningQuestion(const int &userID,const int questionID);
        QSet<int> getConcernedQuestionSet(const int &userID);
        QSet<int> getQuestionSet(const int &userID);
        QSet<int> getMyAnswerSet(const int &userID);
        class User getUserClass(const int &userID);
        QSet<int> getConcernUserSet(const int &userID);
        QSet<int> getFansUserSet(const int &userID);
        QDateTime getAnswerDateTime(const int &answerID);
        QDateTime getQuestionDateTime(const int &questionID);
        EditPersonalInformation *personalInformationFunctionZone;
        int getUserAnswerQuestionID(const int &userID,const int &questionID);
        QString getAnswerContent(const int &answerID);
        void addAnswerOfUser(const int &answerID,const int &userID);
        void addAnswerOfQuestion(const int &questionID,const int &answerID);
        void addQuestionOfUser(const int &questionID,const int &userID);
        void questionContainsSomeString(const QString &content);
        void questionBetweenSomeDateTime(const QDateTime &startDateTime,const QDateTime &endDateTime);
        int getGuideZoneMode();
        void setGuideZoneMode(const int &mode);
        int getAnswerPraiseNum(const int &answerID);
    signals:
        void loginAgain();
    private:
        titleBar *titlebar;
        QHBoxLayout *downLayout;
        QVBoxLayout *mainLayout,*blankWidgetLayout,*rightLayout;
        QLabel *blankLabel,*currentFunctionLabel;
        QScrollArea *scrollArea;
        QWidget *blankWidget;
        void closeEvent(QCloseEvent *e);
        bool nativeEvent(const QByteArray &eventType, void *message, long *result);//实现按住任意位置拖动窗口
        UserListWidget *userListFunctionZone;
        QuestionHeadLineList *questionHeadListFunctionZone;
        QuestionDetailWidget *questionDetailFunctionZone;
        MyAnswerList *answerListFunctionZone;
        AddAnswerPage *addAnswerFunctionZone;
        AddQuestionPage *addQuestionFunctionZone;


        void deleteCurrentFunctionZone();
        void showBackgournd();
        void showEvent(QShowEvent *e);

        void readAllUsers();
        void writeAllUsers();

        void readAllAnswers();
        void writeALLAnswers();

        void readAllQuestions();
        void writeAllQuestions();
   private slots:
        void onUserListButtonClicked();
        void updateUserInfo(class User tmpUser);
        void ShowQuestion(const int &questionID);
        void onAllMyAnswersButtonClicked();
        void onSignOutButtonClicked();
        void updateAvatarInfo();
        void onAddQuestionButtonClicked();
   public slots:
        void onEditPersonalInformationButtonClicked();
        void onAllQuestionsButtonClicked();
        void onRetreatButtonClicked();
        void onAddAnswerButtonClicked(const int &userID,const int &questionID);
        //SimpleButton *allMyAnswers,*allMyFollowers;
};

#endif // MAINWINDOW

