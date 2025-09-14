QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

RC_ICONS += res/img/icon.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# UID 329101171
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data.cpp \
    accountinfodialog.cpp \
    accountinfolistwindow.cpp \
    logindialog.cpp \
    main.cpp \
    recordinfodialog.cpp \
    recordinfolistdialog.cpp \
    searchdialog.cpp

HEADERS += \
    data.h \
    accountinfodialog.h \
    accountinfolistwindow.h \
    logindialog.h \
    recordinfodialog.h \
    recordinfolistdialog.h \
    searchdialog.h

FORMS += \
    accountinfodialog.ui \
    accountinfolistwindow.ui \
    logindialog.ui \
    recordinfodialog.ui \
    recordinfolistdialog.ui \
    searchdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc

DESTDIR=$$PWD/bin

