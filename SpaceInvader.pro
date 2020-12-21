QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audiomanager.cpp \
    clock.cpp \
    enemymanager.cpp \
    gamemanager.cpp \
    graphic-objects/animatedobject.cpp \
    graphic-objects/bullet.cpp \
    graphic-objects/enemy.cpp \
    graphicsview.cpp \
    graphic-objects/hero.cpp \
    keymanager.cpp \
    leaderboard.cpp \
    leaderboardwindow.cpp \
    main.cpp \
    scorebar.cpp \
    graphic-objects/spaceship.cpp \
    startdialog.cpp \
    timer.cpp

HEADERS += \
    audiomanager.h \
    clock.h \
    consts.h \
    coordpair.h \
    graphic-objects/animatedobject.h \
    graphic-objects/bullet.h \
    graphic-objects/checktext.h \
    graphic-objects/enemy.h \
    enemymanager.h \
    gamemanager.h \
    graphicsview.h \
    graphic-objects/hero.h \
    keymanager.h \
    leaderboard.h \
    leaderboardwindow.h \
    scorebar.h \
    graphic-objects/spaceship.h \
    startdialog.h \
    timer.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    Docs/TODO \
    Docs/gameLogic.png
