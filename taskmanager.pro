QT += core gui
QT += multimedia
QT += multimediawidgets
# QT += widgets
RC_ICONS = boji.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    action.cpp \
    askanswer.cpp \
    backgroundcontrol.cpp \
    character.cpp \
    main.cpp \
    mainwindow.cpp \
    processlist.cpp \
    reminder.cpp \
    setting.cpp \
    tipcap.cpp \
    wininfo.cpp \
    workclock.cpp

HEADERS += \
    action.h \
    askanswer.h \
    backgroundcontrol.h \
    character.h \
    mainwindow.h \
    processlist.h \
    reminder.h \
    setting.h \
    stable.h \
    tipcap.h \
    wininfo.h \
    workclock.h

FORMS += \
    askanswer.ui \
    backgroundcontrol.ui \
    character.ui \
    mainwindow.ui \
    processlist.ui \
    reminder.ui \
    setting.ui \
    tipcap.ui \
    wininfo.ui \
    workclock.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    waste

