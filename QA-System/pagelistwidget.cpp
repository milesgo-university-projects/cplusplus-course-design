#include "pagelistwidget.h"

PageListWidget::PageListWidget(QWidget *parent):QWidget(parent)
{
    nextPageButton = new QPushButton;
    lastPageButton = new QPushButton;
    nextPageButton->setText("下一页");
    lastPageButton->setText("上一页");
    nextPageButton->setFocusPolicy(Qt::NoFocus);
    lastPageButton->setFocusPolicy(Qt::NoFocus);
    totalPageLabel = new QLabel;
    pageNumberBox = new QSpinBox;
    goButton = new QPushButton;
    goButton->setFocusPolicy(Qt::NoFocus);
    goButton->setText("Go");

    buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(20);
    buttonLayout->addWidget(lastPageButton,2);
    buttonLayout->addStretch(3);
    buttonLayout->addWidget(nextPageButton,2);
    buttonLayout->addStretch(10);
    buttonLayout->addWidget(totalPageLabel,3);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(pageNumberBox,1);
    buttonLayout->addStretch(0);
    buttonLayout->addWidget(goButton,1);

    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    infoList.clear();

    connect(nextPageButton,SIGNAL(clicked()),this,SLOT(getNextPage()));
    connect(lastPageButton,SIGNAL(clicked()),this,SLOT(getLastPage()));
    connect(goButton,SIGNAL(clicked()),this,SLOT(onGoButtonClicked()));
    connect(this,SIGNAL(pageChanged()),this,SLOT(onPageChanged()));
}

void PageListWidget::init()
{
    int pages=infoList.size()/delta;
    if(infoList.size()%delta!=0)
        pages++;
    pageNumberBox->setRange(1,pages);
    totalPageLabel->setText(QString("共%1页").arg(pages));
    curLow=0,curHigh=delta-1;
    int curBound=qMin(curHigh,infoList.size()-1);
    setItems(curLow,curBound,curHigh);
}

PageListWidget::~PageListWidget()
{
    delete lastPageButton;
    delete nextPageButton;
    delete pageNumberBox;
    delete totalPageLabel;
    delete buttonLayout;
    delete mainLayout;
}

void PageListWidget::getNextPage()
{
    curLow+=delta;
    if(curLow>=infoList.size())
    {
        curLow-=delta;
        return;
    }
    curHigh+=delta;
    int curBound=qMin(curHigh,infoList.size()-1);
    setItems(curLow,curBound,curHigh);
    emit pageChanged();
}

void PageListWidget::getLastPage()
{
    curLow-=delta;
    if(curLow<0)
    {
        curLow+=delta;
        return;
    }
    curHigh-=delta;
    setItems(curLow,curHigh,curHigh);
    emit pageChanged();
}

void PageListWidget::onGoButtonClicked()
{
    int page=pageNumberBox->value();
    int newLow=(page-1)*delta;
    int newHigh=newLow+delta-1;
    int newBound=qMin(newHigh,infoList.size()-1);//waiting for you
    if(newLow!=curLow)
    {
        setItems(newLow,newBound,newHigh);
        curLow=newLow;
        curHigh=newHigh;
        emit pageChanged();
    }
}

void PageListWidget::onPageChanged()
{
    int page=curLow/delta+1;
    pageNumberBox->setValue(page);
}
