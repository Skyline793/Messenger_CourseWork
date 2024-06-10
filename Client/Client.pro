QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = Client
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chat.cpp \
    chatcontroller.cpp \
    chatcreationwindow.cpp \
    loginsettings.cpp \
    loginwindow.cpp \
    main.cpp \
    message.cpp \
    messengerwindow.cpp \
    user.cpp

HEADERS += \
    Commands.h \
    chat.h \
    chatcontroller.h \
    chatcreationwindow.h \
    loginsettings.h \
    loginwindow.h \
    message.h \
    messengerwindow.h \
    user.h

FORMS += \
    chatcreationwindow.ui \
    loginwindow.ui \
    messengerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=
