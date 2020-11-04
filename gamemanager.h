#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "scorebar.h"
#include "graphic-objects/hero.h"
#include "enemymanager.h"
#include "graphicsview.h"
#include "consts.h"

#include <QObject>
#include <QTimer>

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);


private:
    void createFullScreenImage(QString imagePath = nullptr);
    void createBackground();
    void startEnemySpawn();
    void createCountdownTextItem();
    void restartLevel();
    void createWinScreen();
    void connectSpaceshipSignals();
    void deleteSceneGraphicItems();
    void start();
    void setMode(EnemyManager* enemyManager);
    void createLeaderBoardBox();
    QVector <QString> fetchForLeaderBoardInfo();


    QString gameOverImagePath = ImagePaths::gameOverImagePath;
    ScoreBar* scoreBar;
    QGraphicsScene* scene;
    GraphicsView* view;
    Hero* hero = nullptr;
    EnemyManager* enemyManager;
    KeyManager* keyManager;
    QString backgroundImagePath = ImagePaths::backgroundImagePath;
    QGraphicsTextItem* number;
    QGraphicsPixmapItem* fullScreenImage;
    QTimer* countdown = new QTimer();


    bool gameInProcess = false;
    int sceneWidth = 600;
    int sceneHeight = 1000;
    int phase = 3;
    QVector<QString> countdownPhrases = {"START", "1", "2", "3"};
    QSet<int> itemTypesToDelete = {TypeIndex::enemy, TypeIndex::fullscreenText, TypeIndex::bullet};


private slots:
    void gameOver();
    void createEndScreen();
    void changeScore(int score);
    void win();
    void startLevelCountdown();

public slots:
    void keyRPressed();
};

#endif // GAMEMANAGER_H
