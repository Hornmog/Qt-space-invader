#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "level/scorebar.h"
#include "graphic-objects/hero.h"
#include "level/enemymanager.h"
#include "graphicsview.h"
#include "consts.h"
#include "utils/clock.h"
#include "leaderboard.h"
#include "level/audiomanager.h"
#include "level/levelmanager.h"

#include <QObject>
#include <QTimer>

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);


private:
    void connectLevelManager();
    void createWinScreen();
    QString getUserNameEntryBox();
    void createLeaderBoardBox();
    void openMenu();

    KeyManager* keyManager;
    LeaderBoard* leaderBoardFile = new LeaderBoard();
    bool gameWon = false;
    bool gameInProcess = false;
    QGraphicsScene *menuScene;
    GraphicsView* view;
    LevelManager* level1;


private slots:
    void gameOver(int score);
    void win();
    void restartLevel();

public slots:

};

#endif // GAMEMANAGER_H
