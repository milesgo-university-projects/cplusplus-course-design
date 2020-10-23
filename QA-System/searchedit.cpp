#include "searchedit.h"

SearchEdit::SearchEdit(QWidget *parent):QWidget(parent)
{
    accordingToContentRadioButton = new QRadioButton;
    accordingToDateTimeRadioButton = new QRadioButton;
    frame = new QFrame;
    startLabel = new QLabel;
    endLabel = new QLabel;
    startDateTimeEdit = new QDateTimeEdit;
    endDateTimeEdit = new QDateTimeEdit;
    startCalendar = new QCalendarWidget;
    endCalendar = new QCalendarWidget;
    contentEdit = new QLineEdit;
    searchButton = new QPushButton;
    frameLayout = new QHBoxLayout;
    mainLayout = new QHBoxLayout;

    accordingToContentRadioButton->setFocusPolicy(Qt::NoFocus);
    accordingToContentRadioButton->setText("按标题");
    accordingToDateTimeRadioButton->setFocusPolicy(Qt::NoFocus);
    accordingToDateTimeRadioButton->setText("按发布时间");

    contentEdit->setFixedWidth(306);

    startLabel->setText("起");
    endLabel->setText("止");

    startDateTimeEdit->setCalendarPopup(true);
    endDateTimeEdit->setCalendarPopup(true);
    startDateTimeEdit->setCalendarWidget(startCalendar);
    endDateTimeEdit->setCalendarWidget(endCalendar);

    searchButton->setFocusPolicy(Qt::NoFocus);
    searchButton->setText("搜索");

    frameLayout->addWidget(contentEdit);
    frameLayout->addWidget(startLabel);
    frameLayout->addWidget(startDateTimeEdit);
    frameLayout->addWidget(endLabel);
    frameLayout->addWidget(endDateTimeEdit);
    frameLayout->addWidget(searchButton);

    frame->setLayout(frameLayout);
    frame->setStyleSheet(".QFrame{border-width: 1px}");

    mainLayout->addWidget(accordingToContentRadioButton);
    mainLayout->addWidget(accordingToDateTimeRadioButton);
    mainLayout->addWidget(frame);

    setLayout(mainLayout);

    connect(accordingToContentRadioButton,SIGNAL(toggled(bool)),this,SLOT(onRadioButtonClicked()));
    connect(accordingToDateTimeRadioButton,SIGNAL(toggled(bool)),this,SLOT(onRadioButtonClicked()));
    connect(searchButton,SIGNAL(clicked()),this,SLOT(onSearchButtonClicked()));
    connect(contentEdit,SIGNAL(returnPressed()),searchButton,SLOT(click()));
    accordingToContentRadioButton->toggle();
}

void SearchEdit::setMode(const int &mode)
{
    this->mode=mode;
    if(mode==0)
    {//按标题内容搜索
        contentEdit->setHidden(false);
        startLabel->setHidden(true);
        startDateTimeEdit->setHidden(true);
        endLabel->setHidden(true);
        endDateTimeEdit->setHidden(true);
    }
    else if(mode==1)
    {//按发布时间搜索
        contentEdit->setHidden(true);
        startLabel->setHidden(false);
        startDateTimeEdit->setHidden(false);
        endLabel->setHidden(false);
        endDateTimeEdit->setHidden(false);
    }
}

void SearchEdit::onRadioButtonClicked()
{
    if(accordingToContentRadioButton->isChecked())
    {
        setMode(0);
    }
    else
    {
        setMode(1);
    }
}

void SearchEdit::onSearchButtonClicked()
{
    if(mode==0)
    {
        Overall::mainWindow->questionContainsSomeString(contentEdit->text());
    }
    else if(mode==1)
    {
        Overall::mainWindow->questionBetweenSomeDateTime(startDateTimeEdit->dateTime(),endDateTimeEdit->dateTime());
    }
}

SearchEdit::~SearchEdit()
{
    delete accordingToContentRadioButton;
    delete accordingToDateTimeRadioButton;
    delete startLabel;
    delete endLabel;
    delete startCalendar;
    delete startDateTimeEdit;
    delete endCalendar;
    delete endDateTimeEdit;
    delete contentEdit;
    delete searchButton;
    delete frameLayout;
    delete frame;
    delete mainLayout;
}
