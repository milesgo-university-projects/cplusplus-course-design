#ifndef SEARCHEDIT
#define SEARCHEDIT
#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include "twosizebutton.h"
#include "overall.h"

class SearchEdit:public QWidget
{
    Q_OBJECT
    public:
       SearchEdit(QWidget *parent=0);
       ~SearchEdit();
       void setMode(const int &mode);//mode=0表示按标题内容搜索,mode=1表示按发布时间搜索
    private:
       int mode;
       QRadioButton *accordingToContentRadioButton,*accordingToDateTimeRadioButton;
       QFrame *frame;
       QLabel *startLabel,*endLabel;
       QDateTimeEdit *startDateTimeEdit,*endDateTimeEdit;
       QCalendarWidget *startCalendar,*endCalendar;
       QLineEdit *contentEdit;
       QPushButton *searchButton;
       QHBoxLayout *frameLayout,*mainLayout;
    private slots:
       void onRadioButtonClicked();
       void onSearchButtonClicked();
};

#endif // SEARCHEDIT

