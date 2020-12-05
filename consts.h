#ifndef CONS_H
#define CONS_H

#include <QGraphicsItem>
#include <QKeyEvent>
#include <QRandomGenerator>

namespace TypeIndex {
    static const int bullet = 66666;         //anything >= UserType (65536).
    static const int enemy = 66667;
    static const int scoreBar = 66668;
    static const int checkText = 66669;
    static const int hero = 66670;
    static const int background = 3;

    static const int fullscreenText = 7;

}

static const QString leaderBoardFileName = "leaderBoard.json";

namespace JsonNames {
    static const QString enemiesKilled = "kills";
    static const QString name = "name";
    static const QString players = "players";
}

namespace ImagePaths {
    static const QString pathPrefix = ":/images/pictures/";
    static const QString enemy      =  pathPrefix + "enemyOctopus.png";
    static const QString hero       =  pathPrefix + "hero.png";
    static const QString bullet     =  pathPrefix + "bullet.png";
    static const QString enemyBullet=  pathPrefix + "enemyBullet.png";
    static const QString gameOver   =  pathPrefix + "gameOver.png";
    static const QString win        =  pathPrefix + "win.png";
    static const QString background =  pathPrefix + "background.png";
    static const QString pause      =  pathPrefix + "pause.png";
}

namespace ScenePriority {
    static const int spaceship = 10;         //default Zvalue is 0
    static const int fullScreenText = 20;
    static const int bullet = 15;
    static const int text = 30;
    static const int pause = 25;
}

enum Side {
   nobody, hero, enemy, neutral
};

static const int period_ms = 20;
static const double FPS = 1000.0/period_ms;

QSet<int> const verticalMovementKeys = {Qt::Key_Up, Qt::Key_Down};
QSet<int> const horizontalMovementKeys = {Qt::Key_Left, Qt::Key_Right};

QSet<int> const arrowKeys = {Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down};
QSet<int> const heroCommands = {Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down, Qt::Key_Space};

#endif // CONS_H

