#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "scorebar.h"
#include "graphic-objects/hero.h"
#include "enemymanager.h"
#include "graphicsview.h"
#include "consts.h"
#include "leaderboard.h"

#include <QObject>
#include <QTimer>

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);


private:
    QString getUserNameEntryBox();
    void connectSpaceshipSignals();
    void createBackground();
    void createCountdownTextItem();
    void createLeaderBoardBox();
    QGraphicsTextItem *createTextItem();
    void createWinScreen();
    void deleteSceneGraphicItems();
    void restartLevel();
    void openMenu();
    void start();
    void startEnemySpawn();
    void createFullScreenImage(QString imagePath = nullptr);

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
    Timer* countdown = new Timer();
    LeaderBoard* leaderBoardFile = new LeaderBoard();

    bool pause;
    bool gameInProcess = false;
    int sceneWidth = 600;
    int sceneHeight = 1000;
    int phase = 3;
    QVector<QString> countdownPhrases = {"START", "1", "2", "3"};
    QSet<int> itemTypesToKeep = {TypeIndex::hero, TypeIndex::background, TypeIndex::scoreBar};


private slots:
    void gameOver();
    void createEndScreen();
    void changeScore(int score);
    void win();
    void startLevelCountdown();

public slots:
    void keyRPressed();
    void togglePause();
};

#endif // GAMEMANAGER_H
