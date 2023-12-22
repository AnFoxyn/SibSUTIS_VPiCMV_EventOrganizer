QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EventOrganizer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17


SOURCES += \
    addevent.cpp \
    database.cpp \
    editevent.cpp \
    helpinformation.cpp \
    main.cpp \
    mainwindow.cpp \
    settings.cpp

HEADERS += \
    addevent.h \
    database.h \
    editevent.h \
    helpinformation.h \
    mainwindow.h \
    settings.h

FORMS += \
    addevent.ui \
    editevent.ui \
    helpinformation.ui \
    mainwindow.ui \
    settings.ui

RESOURCES += \
    resources/resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
