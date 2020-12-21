#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "audiomanager.h"
#include "enemymanager.h"
#include "graphicsview.h"
#include "keymanager.h"
#include "scorebar.h"

#include <QObject>

#include <graphic-objects/hero.h>

class LevelManager : public QObject
{
    Q_OBJECT
public:
    explicit LevelManager(QObject *parent = nullptr, KeyManager* keyManager = nullptr);

public slots:
    void togglePause();

 private slots:
    void startLevelCountdown(int phase = 3);
    void changeScore(int score);
    void gameOver();

private:
    void start();
    void startEnemySpawn();
    void connectSpaceshipSignals();
    void createBackground();
    void createCountdownTextItem();
    void createPauseSceen();
    //    void deleteSceneGraphicItems();

    bool gameInProcess = false;
    ScoreBar* scoreBar;
    QGraphicsScene* scene;
    Hero* hero = nullptr;
    EnemyManager* enemyManager;
    AudioManager* audioManager;
    QGraphicsPixmapItem* pause;
    QGraphicsTextItem* number;
    Clock* clock = Clock::getClock();
    Timer* countdown = new Timer();

    int pauseWidth  = 230;
    int pauseHeight = 230;
    int phase = 3;
signals:
    void win();
};

#endif // LEVELMANAGER_H
