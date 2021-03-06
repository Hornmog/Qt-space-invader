QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
RC_FILE = spaceinvader.rc


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
    gamemanager.cpp \
    graphic-objects/animatedobject.cpp \
    graphic-objects/bullet.cpp \
    graphic-objects/chargebar.cpp \
    graphic-objects/enemy.cpp \
    graphic-objects/meteor.cpp \
    graphic-objects/movingobject.cpp \
    graphicsview.cpp \
    graphic-objects/hero.cpp \
    keymanager.cpp \
    leaderboard.cpp \
    leaderboardwindow.cpp \
    level/audiomanager.cpp \
    level/enemycommander.cpp \
    level/healthbar.cpp \
    level/levelmanager.cpp \
    level/meteorcommander.cpp \
    level/scorebar.cpp \
    level/soundeffect.cpp \
    main.cpp \
    graphic-objects/spaceship.cpp \
    startdialog.cpp \
    utils/clock.cpp \
    utils/timer.cpp

HEADERS += \
    consts.h \
    graphic-objects/animatedobject.h \
    graphic-objects/bullet.h \
    graphic-objects/chargebar.h \
    graphic-objects/checktext.h \
    graphic-objects/enemy.h \
    gamemanager.h \
    graphic-objects/meteor.h \
    graphic-objects/movingobject.h \
    graphicsview.h \
    graphic-objects/hero.h \
    keymanager.h \
    leaderboard.h \
    leaderboardwindow.h \
    level/audiomanager.h \
    level/enemycommander.h \
    level/healthbar.h \
    level/levelmanager.h \
    graphic-objects/spaceship.h \
    level/meteorcommander.h \
    level/scorebar.h \
    level/soundeffect.h \
    startdialog.h \
    utils/clock.h \
    utils/coordpair.h \
    utils/timer.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    Docs/TODO \
    Docs/model.qmodel \
    spaceinvader.rc
