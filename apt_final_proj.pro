QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_CXXFLAGS += -fconcepts-diagnostics-depth=200

SOURCES += \
    customqgraphicsview.cpp \
    enemyview.cpp \
    gamecontroller.cpp \
    graphicrender.cpp \
    healthpackview.cpp \
    level.cpp \
    levelmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    overlayrender.cpp \
    pathfinderhelper.cpp \
    pathfindernode.cpp \
    protagonistview.cpp \
    rendermethod.cpp \
    textrender.cpp \
    tileview.cpp \
    view.cpp

HEADERS += \
    customqgraphicsview.h \
    enemyview.h \
    gamecontroller.h \
    graphicrender.h \
    healthpackview.h \
    level.h \
    levelmanager.h \
    mainwindow.h \
    mainwindow.h \
    overlayrender.h \
    pathfinder_class.h \
    pathfinderhelper.h \
    pathfindernode.h \
    protagonistview.h \
    rendermethod.h \
    textrender.h \
    tileview.h \
    view.h

FORMS += \
    mainwindow.ui

# QT_LOGGING_CONF=./qtlogging.ini

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/worldlib/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/worldlib/debug/ -lworld
else:unix: LIBS += -L$$PWD/worldlib/ -lworld

INCLUDEPATH += $$PWD/worldlib
DEPENDPATH += $$PWD/worldlib

RESOURCES = application.qrc

DISTFILES +=
