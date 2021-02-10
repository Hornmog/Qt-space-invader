#ifndef CONS_H
#define CONS_H

#include <QFont>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>

namespace TypeIndex {
    static const int bullet = 66666;         //anything >= UserType (65536).
    static const int enemy = 66667;
    static const int scoreBar = 66668;
    static const int checkText = 66669;
    static const int hero = 66670;
    static const int background = 3;

    static const int fullscreenText = 7;

}

static const QVector<QString> countdownPhrases = {"START", "1", "2", "3"};
static const QSet<int> itemTypesToKeep = {TypeIndex::background, TypeIndex::scoreBar, TypeIndex::checkText};

static const QString leaderBoardFileName = "leaderBoard.json";

namespace JsonNames {
    static const QString enemiesKilled = "kills";
    static const QString name = "name";
    static const QString players = "players";
}

namespace ImagePaths {
    static const QString pathPrefix = ":/images/pictures/";
    static const QString enemy      =  pathPrefix + "enemyOctopus.png";
    static const QString hero       =  pathPrefix + "hero.gif";
    static const QString damagedHero=  pathPrefix + "damagedHero.gif";
    static const QString bullet     =  pathPrefix + "bulletFast.gif";
    static const QString enemyBullet=  pathPrefix + "bulletFastWhite.gif";
    static const QString gameOver   =  pathPrefix + "gameOver.png";
    static const QString pressR     =  pathPrefix + "pressR.png";
    static const QString win        =  pathPrefix + "win.png";
    static const QString background =  pathPrefix + "background.png";
    static const QString pause      =  pathPrefix + "pause.png";
    static const QString heart      =  pathPrefix + "heart.png";
}

namespace AudioPaths {
    static const QString pathPrefix          =  ":/music/audio/";
    static const QString background          =  pathPrefix + "background4.wav";
    static const QString gameOver            =  pathPrefix + "gameOver.wav";
    static const QVector<QString> heroShoot  = {pathPrefix + "heroShoot/1.wav",
                                                pathPrefix + "heroShoot/2.wav",
                                                pathPrefix + "heroShoot/3.wav",
                                                pathPrefix + "heroShoot/4.wav",
                                                pathPrefix + "heroShoot/5.wav"};
    static const QVector<QString> heroDamaged= {pathPrefix + "heroDamaged/1.wav",
                                                pathPrefix + "heroDamaged/2.wav",
                                                pathPrefix + "heroDamaged/3.wav"};
}

namespace ScenePriority {
    static const int spaceship = 10;         //default Zvalue is 0
    static const int meteor = 9;
    static const int fullScreenText = 20;
    static const int bullet = 15;
    static const int text = 30;
    static const int pause = 25;
    static const int heroAttributes = 19;
}
namespace Volume {
    static const float heroShoot = 0.2;
    static const float heroDamaged = 0.3;
}

enum Side {
   nobody, hero, enemy, neutral
};

static const int period_ms = 15;
static const double FPS = 1000.0/period_ms;

static const int sceneWidth  = 600;
static const int sceneHeight = 1000;

QSet<int> const verticalMovementKeys = {Qt::Key_Up, Qt::Key_Down};
QSet<int> const horizontalMovementKeys = {Qt::Key_Left, Qt::Key_Right};

QSet<int> const arrowKeys = {Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down};
QSet<int> const heroCommands = {Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down, Qt::Key_Space};

class UtilityFunctions {
public:
        static QGraphicsTextItem* createTextItem() {
        QGraphicsTextItem* item = new QGraphicsTextItem();
        QFont font = QFont("Impact", 40, QFont::Bold);
        item->setFont(font);
        item->setDefaultTextColor(QColor(156, 20, 68));
        item->setZValue(ScenePriority::text);
        return item;
    }
};

#endif // CONS_H

