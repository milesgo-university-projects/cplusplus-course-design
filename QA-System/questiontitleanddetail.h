#ifndef QUESTIONTITLEANDDETAIL
#define QUESTIONTITLEANDDETAIL
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateTime>
#include "overall.h"

class QuestionTitleAndDetail:public QFrame
{
    Q_OBJECT
    public:
        QuestionTitleAndDetail(QWidget *parent=0);
        ~QuestionTitleAndDetail();
        void setInfo(QString title,QString detail,QDateTime dateTime,QString userName,int answerAmount,int userID,int questionID);
        void clearInfo();
        void setMode(const int &mode);//0表示某一提问的详细情况，1表示提问列表（全部提问、我关注的提问）
        void setQuesitonID(const int &questionID);
        int getUserID();
        QPushButton *addOrChangeAnswerButton;
    private:
        int questionID;
        int userID;
        int currentUserAnswerID;
        bool isAuthorConcerned;
        bool isQuestionConcerned;
        QLabel *titleLabel,*detailLabel;
        QLabel *userNameLabel,*dateTimeLabel,*answerAmountLabel;
        QHBoxLayout *infoLayout;
        QVBoxLayout *mainLayout;
        QPushButton *intoDetailButton,*concernUserButton,*concernQuestionButton,*sortButton;
        QHBoxLayout *buttonLayout;
    private slots:
        void onSortButtonClicked();
        void onIntoDetailButtonClicked();
        void onConcernUserButtonClicked();
        void onConcernQuestionButtonClicked();
        void onAddOrChangeAnswerButtonClicked();
    public slots:
        void updateConcernOrNotButton();
    signals:
        void sortSignal(int flag);//0表示按照时间排序，1表示按照赞数排序
        void showQuestionSignal(int questionID);
        void addOrChangeAnswerSignal(int userID,int questionID);
        void concernStateChanged(int userID);
};

#endif // QUESTIONTITLEANDDETAIL

