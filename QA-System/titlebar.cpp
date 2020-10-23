#include "titlebar.h"
#include <QDebug>

titleBar::titleBar(QWidget *parent):QWidget(parent)
{
    setFixedHeight(60);
    isPressed=false;

    closeButton = new QPushButton;
    minSizeButton = new QPushButton;
    closeButtonLabel = new QLabel(closeButton);
    minSizeButtonLabel = new QLabel(minSizeButton);

    iconLabel = new QLabel;
    titleLabel = new QLabel;
    titleLayout = new QHBoxLayout;

    iconLabel->setFixedSize(20,20);
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(QPixmap("../data/images/che.png"));

    closeButton->setFixedSize(26,26);
    minSizeButton->setFixedSize(26,26);
    closeButtonLabel->setFixedSize(26,26);
    minSizeButtonLabel->setFixedSize(26,26);

    closeButtonLabel->setAttribute(Qt::WA_TranslucentBackground);
    minSizeButtonLabel->setAttribute(Qt::WA_TranslucentBackground);
    closeButtonLabel->setPixmap(QPixmap("../data/images/close.png"));
    minSizeButtonLabel->setPixmap(QPixmap("../data/images/minimize.png"));
    titleLabel->setText(tr("瞎扯问答系统"));

    closeButton->setObjectName("closeButton");
    minSizeButton->setObjectName("minSizeButton");
    titleLabel->setObjectName("titleLabel");

    closeButton->setToolTip(tr("关闭"));
    minSizeButton->setToolTip(tr("最小化"));

    closeButton->setFocusPolicy(Qt::NoFocus);
    minSizeButton->setFocusPolicy(Qt::NoFocus);

    lastPageButton = new twoSizeButton("lastPage_16px","lastPage_24px",QSize(30,30),QSize(16,16),QSize(24,24));
    lastPageButton->setStyleSheet("border-width: 0px");

    searchEdit = new SearchEdit;

    titleLayout->addStretch(0);
    titleLayout->addWidget(iconLabel,2);
    titleLayout->addStretch(0);
    titleLayout->addWidget(titleLabel,5);
    titleLayout->addStretch(1);
    titleLayout->addWidget(lastPageButton,3);
    titleLayout->addStretch(2);
    titleLayout->addWidget(searchEdit);
    titleLayout->addStretch(75);
    titleLayout->addWidget(minSizeButton,3);
    titleLayout->addStretch(0);
    titleLayout->addWidget(closeButton,3);
    titleLayout->addStretch(0);
    titleLayout->setContentsMargins(5,0,5,0);
    setLayout(titleLayout);

    connect(closeButton,SIGNAL(clicked()),this,SLOT(onClicked()));
    connect(minSizeButton,SIGNAL(clicked()),this,SLOT(onClicked()));
}

titleBar::~titleBar()
{
    delete closeButton;
    delete minSizeButton;
    delete iconLabel;
    delete titleLabel;
    delete closeButtonLabel;
    delete minSizeButtonLabel;
    delete searchEdit;
    delete titleLayout;
}

void titleBar::mouseMoveEvent(QMouseEvent *e)
{
    if(isPressed)
    {
        QWidget *controledWindow = this->window();
        controledWindow->move(controledWindow->pos()+e->pos()-point);
    }
}

void titleBar::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        isPressed=true;
        point=e->pos();
    }
}

void titleBar::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    isPressed=false;
}

void titleBar::onClicked()
{
    QPushButton *pushedButton = qobject_cast<QPushButton *>(sender());
    QWidget *controledWindow = this->window();

    if(controledWindow->isTopLevel())
    {
        if(pushedButton==closeButton)
        {
            controledWindow->close();
        }
        else if(pushedButton==minSizeButton)
        {
            controledWindow->showMinimized();
        }
    }
}

bool titleBar::eventFilter(QObject *obj, QEvent *e)
{
    QWidget *pwidget=qobject_cast<QWidget *>(obj);
    switch(e->type())
    {
        case QEvent::WindowTitleChange:
        {
            if(pwidget)
            {
                titleLabel->setText(pwidget->windowTitle());
            }
            return true;
        }
        case QEvent::WindowIconChange:
        {
            if(pwidget)
            {
                QIcon icon=pwidget->windowIcon();
                iconLabel->setPixmap(icon.pixmap(iconLabel->size()));
            }
            return true;
        }
        default:
            break;
    }
    return QWidget::eventFilter(obj,e);
}
