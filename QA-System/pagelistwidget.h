#ifndef PAGELISTWIDGET
#define PAGELISTWIDGET
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QSpinBox>
#include <QLabel>

class PageListWidget:public QWidget
{
    Q_OBJECT
    public:
        PageListWidget(QWidget *parent=0);
        ~PageListWidget();
    protected:
        int delta,curLow,curHigh;
        QPushButton *nextPageButton,*lastPageButton,*goButton;
        QSpinBox *pageNumberBox;
        QLabel *totalPageLabel;
        QHBoxLayout *buttonLayout;
        QVBoxLayout *mainLayout;
        QList<int> infoList;
        virtual void setItems(int ll,int rr,int bound) = 0;
        void init();
    protected slots:
        virtual void getNextPage();
        virtual void getLastPage();
        void onGoButtonClicked();
        void onPageChanged();
    signals:
        void pageChanged();
};

#endif // PAGELISTWIDGET

