#-------------------------------------------------
#
# Project created by QtCreator 2013-11-29T01:05:17
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ITS
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Db.cpp \
    NewLearnerDialog.cpp \
    LoginDialog.cpp \
    Learner.cpp \
    SqlQuery.cpp \
    ImageDelegate.cpp \
    Session.cpp \
    Gender.cpp \
    Phrase.cpp \
    DictionaryDialog.cpp \
    AddPhraseDialog.cpp

HEADERS  += MainWindow.h \
    Db.h \
    NewLearnerDialog.h \
    LoginDialog.h \
    Learner.h \
    SqlQuery.h \
    ImageDelegate.h \
    Session.h \
    Gender.h \
    Phrase.h \
    DictionaryDialog.h \
    AddPhraseDialog.h

FORMS    += MainWindow.ui \
    NewLearnerDialog.ui \
    LoginDialog.ui \
    DictionaryDialog.ui \
    AddPhraseDialog.ui

RESOURCES += \
    ITS.qrc
