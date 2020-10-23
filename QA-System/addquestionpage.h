#ifndef ADDQUESTIONPAGE
#define ADDQUESTIONPAGE
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "sizelimitedtextedit.h"
#include "overall.h"

class AddQuestionPage:public QWidget
{
    Q_OBJECT
    public:
        AddQuestionPage(QWidget *parent=0);
        ~AddQuestionPage();
    private:
        QPushButton *clearButton,*submitButton;
        SizeLimitedTextEdit *titleEdit,*detailEdit;
        QHBoxLayout *buttonLayout;
        QVBoxLayout *mainLayout;
    private slots:
        void onClearButtonClicked();
        void onSubmitButtonClicked();
    signals:
        void toAllQuestionFunctionZone();
};

#endif // ADDQUESTIONPAGE

