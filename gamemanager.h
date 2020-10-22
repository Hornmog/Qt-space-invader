#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "scorebar.h"
#include "graphic-objects/hero.h"
#include "enemymanager.h"
#include "graphicsview.h"
#include "consts.h"

#include <QObject>

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);


private:
    void createFullScreenImage(QString imagePath);
    void createBackground();
    void startEnemySpawn();
    void createCountdownTextItem();

    QString gameOverImagePath = ImagePaths::gameOverImagePath;
    ScoreBar* scoreBar;
    QGraphicsScene* scene;
    GraphicsView* view;
    Hero* hero;
    EnemyManager* enemyManager;
    QString backgroundImagePath = ImagePaths::backgroundImagePath;
    QGraphicsTextItem* number;

    int sceneWidth = 600;
    int sceneHeight = 1000;
    int phase = 3;
    QVector<QString> countdownPhrases = {"START", "1", "2", "3"};



private slots:
    void gameOver();
    void createEndScreen();
    void changeScore(int score);
    void createWinScreen();
    void startLevelCountdown();

};

#endif // GAMEMANAGER_H
