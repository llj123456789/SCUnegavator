QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    infowin.cpp \
    login.cpp \
    main.cpp \
    mygraphicsview.cpp \
    myitem.cpp \
    negvator.cpp \
    set.cpp \
    user.cpp

HEADERS += \
    infowin.h \
    login.h \
    mygraphicsview.h \
    myitem.h \
    negvator.h \
    road_node.h \
    set.h \
    user.h

FORMS += \
    infowin.ui \
    login.ui \
    negvator.ui \
    set.ui \
    user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    scr1.qrc

QT +=sql
QT+=axcontainer

DISTFILES +=

