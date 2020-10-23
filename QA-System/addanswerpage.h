#ifndef ADDANSWERPAGE
#define ADDANSWERPAGE
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QShowEvent>
#include "overall.h"
#include "sizelimitedtextedit.h"

class AddAnswerPage:public QWidget
{
    Q_OBJECT
    public:
        AddAnswerPage(int userID=0,int questionID=0,QWidget *parent=0);
        ~AddAnswerPage();
    private:
        int answerID;//-1表示新建回答，否则表示编辑已有回答
        int questionID;
        QPushButton *cancelButton,*submitButton;
        SizeLimitedTextEdit *textEdit;
        QHBoxLayout *buttonLayout;
        QVBoxLayout *mainLayout;
        void showEvent(QShowEvent *e);
    private slots:
        void onCancelButtonClicked();
        void onSubmitButtonClicked();
};

#endif // ADDANSWERPAGE

