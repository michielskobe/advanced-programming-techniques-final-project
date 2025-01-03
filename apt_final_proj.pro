QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_CXXFLAGS += -fconcepts-diagnostics-depth=200

SOURCES += \
    autoplaycontroller.cpp \
    difficultycontroller.cpp \
    gamecontroller.cpp \
    graphicalenemyview.cpp \
    graphicalhealthpackview.cpp \
    graphicaloverlayview.cpp \
    graphicalprotagonistview.cpp \
    graphicalview.cpp \
    graphicalworldview.cpp \
    level.cpp \
    levelmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    ownenemy.cpp \
    ownpenemy.cpp \
    pathfinderhelper.cpp \
    pathfindernode.cpp \
    textualenemyview.cpp \
    textualhealthpackview.cpp \
    textualprotagonistview.cpp \
    textualview.cpp \
    textualworldview.cpp \
    view.cpp \
    xenemy.cpp

HEADERS += \
    autoplaycontroller.h \
    difficultycontroller.h \
    gamecontroller.h \
    graphicalenemyview.h \
    graphicalhealthpackview.h \
    graphicaloverlayview.h \
    graphicalprotagonistview.h \
    graphicalview.h \
    graphicalworldview.h \
    level.h \
    levelmanager.h \
    mainwindow.h \
    mainwindow.h \
    ownenemy.h \
    ownpenemy.h \
    pathfinder_class.h \
    pathfinderhelper.h \
    pathfindernode.h \
    textualenemyview.h \
    textualhealthpackview.h \
    textualprotagonistview.h \
    textualview.h \
    textualworldview.h \
    view.h \
    xenemy.h

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
