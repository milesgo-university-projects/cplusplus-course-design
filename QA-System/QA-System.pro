#-------------------------------------------------
#
# Project created by QtCreator 2020-10-23T12:55:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QA-System
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    addanswerpage.cpp \
    addquestionpage.cpp \
    answer.cpp \
    basicinfo.cpp \
    dividewidget.cpp \
    editpersonalinformation.cpp \
    functions.cpp \
    guidezone.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    myanswerlist.cpp \
    overall.cpp \
    pagelistwidget.cpp \
    question.cpp \
    questiondetailwidget.cpp \
    questionheadlinelist.cpp \
    questiontitleanddetail.cpp \
    searchedit.cpp \
    signupwidget.cpp \
    simplebutton.cpp \
    singleansweritem.cpp \
    sizelimitedtextedit.cpp \
    titlebar.cpp \
    twosizebutton.cpp \
    user.cpp \
    useritem.cpp \
    userlistwidget.cpp

HEADERS += \
    addanswerpage.h \
    addquestionpage.h \
    answer.h \
    basicinfo.h \
    dividewidget.h \
    editpersoninformation.h \
    functions.h \
    guidezone.h \
    loginwidget.h \
    mainwindow.h \
    myanswerlist.h \
    overall.h \
    pagelistwidget.h \
    question.h \
    questiondetailwidget.h \
    questionheadlinelist.h \
    questiontitleanddetail.h \
    searchedit.h \
    signupwidget.h \
    simplebutton.h \
    singleansweritem.h \
    sizelimitedtextedit.h \
    titlebar.h \
    twosizebutton.h \
    user.h \
    useritem.h \
    userlistwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
