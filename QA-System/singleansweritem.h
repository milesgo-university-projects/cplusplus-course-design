#ifndef SINGLEANSWERITEM
#define SINGLEANSWERITEM
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRgb>
#include <QPushButton>
#include "answer.h"
#include "mainwindow.h"
#include "twosizebutton.h"

class SingleAnswerItem:public QFrame
{
    Q_OBJECT
    public:
        SingleAnswerItem(QWidget *parent=0);
        ~SingleAnswerItem();
        void setAnswer(const int &answerID);
        void clearInfo();
        int getUserID();
    private:
        QLabel *contentLabel,*userNameLabel,*dateTimeLabel,*praiseNumLabel;
        twoSizeButton *praiseButton;
        QLabel *alreadyPraisedLabel;
        QHBoxLayout *infoLayout;
        QVBoxLayout *mainLayout;
        QPushButton *concernUserButton;
        int answerID;
        int userID;
        int praiseNum;
    private slots:
        void onPraiseButtonClicked();
        void onConcernUserButtonClicked();
    public slots:
        void updateConcernUserButton();
    signals:
        void concernStateChanged(int userID);
};

#endif // SINGLEANSWERITEM

