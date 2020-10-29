#ifndef CONS_H
#define CONS_H

#include <QGraphicsItem>
#include <QKeyEvent>

namespace TypeIndex {
    static const int bullet = 66666;         //anything >= UserType (65536).
    static const int enemy = 66667;
    static const int scoreBar = 666678;
    static const int background = 3;
    static const int hero = 66670;
    static const int fullscreenText = 7;
}

namespace ImagePaths {
    static const QString pathPrefix = ":/images/pictures/";
    static const QString enemyImagePath =         pathPrefix + "enemy.png";
    static const QString heroImagePath =          pathPrefix + "hero.png";
    static const QString bulletImagePath =        pathPrefix + "bullet.png";
    static const QString enemyBulletImagePath =   pathPrefix + "enemyBullet.png";
    static const QString gameOverImagePath =      pathPrefix + "gameOver.png";
    static const QString winImagePath =           pathPrefix + "win.png";
    static const QString backgroundImagePath =    pathPrefix + "background.png";
}

namespace ScenePriority {
    static const int spaceship = 10;         //default Zvalue is 0
    static const int fullScreenText = 20;
    static const int bullet = 15;
    static const int text = 30;
}

namespace Side {
    static const int nobody = 0;
    static const int hero = 1;
    static const int enemy = 2;
    static const int neutral = 3;
}

static const int period_ms = 20;
static const double FPS = 1000.0/period_ms;
#endif // CONS_H

