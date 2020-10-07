#ifndef CONS_H
#define CONS_H

#include <QGraphicsItem>

namespace Keys {
    static const int bulletIndex = 66666;         //anything >= UserType (65536).
    static const int enemyIndex = 66667;
}

namespace ImagePaths {
    static const QString pathPrefix = ":/images/";
    static const QString enemyImagePath =         pathPrefix + "enemy.png";
    static const QString heroImagePath =          pathPrefix + "hero.png";
    static const QString bulletImagePath =        pathPrefix + "bullet.png";
    static const QString enemyBulletImagePath =   pathPrefix + "enemyBullet.png";
    static const QString gameOverImagePath =      pathPrefix + "gameOver.png";
    static const QString winImagePath =           pathPrefix + "win.png";
    static const QString backgroundImagePath =    pathPrefix + "background.png";
}

#endif // CONS_H

