#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "scorebar.h"
#include "graphic-objects/hero.h"
#include "enemymanager.h"
#include "graphicsview.h"
#include "consts.h"
#include "clock.h"
#include "leaderboard.h"
#include "audiomanager.h"
#include "levelmanager.h"

#include <QObject>
#include <QTimer>

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);


private:
    void createWinScreen();
    QString getUserNameEntryBox();
    void createLeaderBoardBox();
    void openMenu();
    void restartLevel();

    KeyManager* keyManager;
    AudioManager* audioManager;
    LeaderBoard* leaderBoardFile = new LeaderBoard();
    bool gameWon = false;
    bool gameInProcess = false;
    QGraphicsScene *menuScene;
    GraphicsView* view;
    LevelManager* level1;


private slots:
    void gameOver(int score);
    void win();


public slots:
    void keyRPressed();
};

#endif // GAMEMANAGER_H
