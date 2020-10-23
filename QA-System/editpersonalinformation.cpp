#include "editpersoninformation.h"

EditPersonalInformation::EditPersonalInformation(QWidget *parent):QFrame(parent)
{

}

EditPersonalInformation::EditPersonalInformation(const int &userID,const int &mode,QWidget *parent):QFrame(parent)
{
    avatarChanged=false;
    if(Overall::windowControl)
    {
        int loc=Overall::windowStack.size();
        Overall::windowStack.push(mode+1);
        Overall::stackLocationToID[loc]=userID;
        Overall::stackLocationToMineOrHis[loc]=Overall::mainWindow->getGuideZoneMode();
    }
    userNameLabel = new QLabel;
    userNameLabel->setText("用户名：");
    userNameLabel->setStyleSheet("border-width: 0px");
    introductionLabel = new QLabel;
    introductionLabel->setStyleSheet("border: 0px");
    introductionLabel->setText("个人介绍:");
    birthdayLabel = new QLabel;
    birthdayLabel->setStyleSheet("border-width: 0px");
    birthdayLabel->setText("生日：");
    genderLabel = new QLabel;
    genderLabel->setStyleSheet("border-width: 0px");
    genderLabel->setText("性别：");
    statisticLabel = new QLabel;

    userNameEdit = new QLineEdit;
    userNameEdit->setFocusPolicy(Qt::NoFocus);
    introductionEdit = new QTextEdit;
    birthdayEdit = new QDateEdit;

    birthdayEdit->setCalendarPopup(true);
    calendar = new QCalendarWidget;
    birthdayEdit->setCalendarWidget(calendar);

    radioButtonMale = new QRadioButton;
    radioButtonMale->setText("男");
    radioButtonMale->setStyleSheet("border-width: 0px");
    radioButtonFemale = new QRadioButton;
    radioButtonFemale->setText("女");
    radioButtonFemale->setStyleSheet("border-width: 0px");
    radioButtonUnknown = new QRadioButton;
    radioButtonUnknown->setText("保密");
    radioButtonUnknown->setStyleSheet("border-width: 0px");

    avatarLabel = new QLabel;
    avatarLabel->setStyleSheet("border-width: 0px");
    changeAvatarButton = new QPushButton;
    changeAvatarButton->setText("更改头像");
    changeAvatarButton->setFocusPolicy(Qt::NoFocus);
    avatarLabel->setText("hahahaha");

    avatarLayout = new QVBoxLayout;
    avatarLayout->addStretch(0);
    avatarLayout->addWidget(avatarLabel,6);
    avatarLayout->setAlignment(avatarLabel,Qt::AlignHCenter);
    avatarLayout->addStretch(1);
    avatarLayout->addWidget(changeAvatarButton,2);
    avatarLayout->setAlignment(changeAvatarButton,Qt::AlignHCenter);
    avatarLayout->addStretch(1);

    userNameLayout = new QHBoxLayout;
    userNameLayout->addWidget(userNameLabel,1);
    userNameLayout->addWidget(userNameEdit,3);

    birthdayLayout = new QHBoxLayout;
    birthdayLayout->addWidget(birthdayLabel,1);
    birthdayLayout->addWidget(birthdayEdit,3);

    genderLayout = new QHBoxLayout;
    genderLayout->addWidget(genderLabel,2);
    genderLayout->addStretch(1);
    genderLayout->addWidget(radioButtonMale,2);
    genderLayout->addStretch(1);
    genderLayout->addWidget(radioButtonFemale,2);
    genderLayout->addStretch(1);
    genderLayout->addWidget(radioButtonUnknown,2);

    vLayout = new QVBoxLayout;
    vLayout->addLayout(userNameLayout);
    vLayout->addStretch(2);
    vLayout->addLayout(genderLayout);
    vLayout->addStretch(2);
    vLayout->addLayout(birthdayLayout);
    vLayout->addStretch(2);
    vLayout->addWidget(statisticLabel);
    vLayout->addStretch(2);

    subHorizontalLayout = new QHBoxLayout;
    subHorizontalLayout->addLayout(vLayout,5);
    subHorizontalLayout->addStretch(1);
    subHorizontalLayout->addLayout(avatarLayout,6);
    subHorizontalLayout->addStretch(1);

    saveButton = new QPushButton;
    saveButton->setFocusPolicy(Qt::NoFocus);
    saveButton->setText("保存");

    mainLayout = new QVBoxLayout;
    mainLayout->addStretch(2);
    mainLayout->addLayout(subHorizontalLayout,5);
    mainLayout->addStretch(1);
    mainLayout->addWidget(introductionLabel,1);
    mainLayout->addStretch(0);
    mainLayout->addWidget(introductionEdit,5);
    mainLayout->addStretch(1);
    mainLayout->addWidget(saveButton);
    mainLayout->setAlignment(saveButton,Qt::AlignHCenter);
    mainLayout->addStretch(2);

    setLayout(mainLayout);

    //读入基本信息
    rec=new class User;
    *rec=Overall::mainWindow->getUserClass(userID);
    userNameEdit->setText(rec->getUserName());
    birthdayEdit->setDate(rec->getBirthday());
    int gender=rec->getGender();
    if(gender==0)
        radioButtonMale->setChecked(true);
    else if(gender==1)
        radioButtonFemale->setChecked(true);
    else
        radioButtonUnknown->setChecked(true);
    introductionEdit->setText(rec->getIntroduction());

    statisticLabel->setText(QString("统计信息         回答:%1·提问:%2·关注:%3·粉丝:%4·获赞:%5").arg(rec->getMyAnswersSize()).arg(rec->getMyQuestionsSize()).arg(rec->getconcernUsersSize()).arg(rec->getFansSize()).arg(rec->getPraiseNum()));

    //读入头像
    QFile file;
    avatarPath="../data/user/avatar/"+QString("%1").arg(rec->getUserID())+"_big.png";
    file.setFileName(avatarPath);
    if(!file.open(QIODevice::ReadOnly))
        avatarPath="../data/user/avatar/default_big.png";
    else
        file.close();
    avatarLabel->setPixmap(QPixmap(avatarPath));
    if(mode==0)
    {
        connect(saveButton,SIGNAL(clicked()),this,SLOT(onSaveButtonClicked()));
        connect(changeAvatarButton,SIGNAL(clicked()),this,SLOT(onChangeAvatarButtonClicked()));
    }
    else if(mode==1)
    {
        birthdayEdit->setFocusPolicy(Qt::NoFocus);
        birthdayEdit->setCalendarPopup(false);
        birthdayEdit->setMaximumDate(birthdayEdit->date());
        birthdayEdit->setMinimumDate(birthdayEdit->date());
        if(radioButtonMale->isChecked())
        {
            radioButtonFemale->setEnabled(false);
            radioButtonUnknown->setEnabled(false);
        }
        else if(radioButtonFemale->isChecked())
        {
            radioButtonMale->setEnabled(false);
            radioButtonUnknown->setEnabled(false);
        }
        else if(radioButtonUnknown->isChecked())
        {
            radioButtonMale->setEnabled(false);
            radioButtonFemale->setEnabled(false);
        }
        radioButtonMale->setFocusPolicy(Qt::NoFocus);
        radioButtonFemale->setFocusPolicy(Qt::NoFocus);
        radioButtonUnknown->setFocusPolicy(Qt::NoFocus);
        introductionEdit->setFocusPolicy(Qt::NoFocus);
        saveButton->setHidden(true);
        changeAvatarButton->setHidden(true);
    }
}

EditPersonalInformation::~EditPersonalInformation()
{
    delete userNameLabel;
    delete introductionLabel;
    delete genderLabel;
    delete birthdayLabel;
    delete avatarLabel;
    delete statisticLabel;
    delete userNameEdit;
    delete introductionEdit;
    delete calendar;
    delete birthdayEdit;
    delete radioButtonMale;
    delete radioButtonFemale;
    delete radioButtonUnknown;
    delete changeAvatarButton;
    delete saveButton;
    delete userNameLayout;
    delete birthdayLayout;
    delete genderLayout;
    delete vLayout;
    delete avatarLayout;
    delete subHorizontalLayout;
    delete mainLayout;
}

void EditPersonalInformation::showEvent(QShowEvent *e)
{
    QFrame::showEvent(e);
}

void EditPersonalInformation::onSaveButtonClicked()
{
    QDate date=birthdayEdit->date();
    int gender;
    if(radioButtonMale->isChecked())
        gender=0;
    else if(radioButtonFemale->isChecked())
        gender=1;
    else
        gender=2;
    rec->setGender(gender);
    rec->setBirthday(date);
    rec->setIntroduction(introductionEdit->toPlainText());
    emit userInfoUpdated(*rec);
    if(avatarChanged)
    {
        QPixmap pixmap=QPixmap(avatarPath);
        QPixmap bigPixmap=pixmap.scaled(256,256);
        QPixmap normalPixmap=pixmap.scaled(60,60);
        bigPixmap.save("../data/user/avatar/"+QString("%1").arg(Overall::currentUserID)+"_big.png");
        normalPixmap.save("../data/user/avatar/"+QString("%1").arg(Overall::currentUserID)+".png");
        emit avatarChangedSignal();
        avatarChanged=false;
    }
    QMessageBox message(QMessageBox::Information,"恭喜","保存成功！",QMessageBox::Yes,NULL);
    message.setButtonText(QMessageBox::Yes,"好的");
    message.exec();
}

void EditPersonalInformation::onChangeAvatarButtonClicked()
{
    avatarPath=QFileDialog::getOpenFileName(this,tr("请选择png类型的图片"),".",tr("Images Files(*.png)"));
    if(!avatarPath.isEmpty())
    {
        avatarLabel->setPixmap(QPixmap(avatarPath).scaled(256,256));
        avatarChanged=true;
    }
}
