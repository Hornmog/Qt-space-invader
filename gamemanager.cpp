#include <climits>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QInputDialog>
#include <QDir>

#include "gamemanager.h"
#include "graphic-objects/enemy.h"
#include "startdialog.h"
#include "leaderboardwindow.h"
#include "clock.h"

GameManager::GameManager(QObject *parent) : QObject(parent)
{
    // openMenu(); ??
    // Easter Egg for default scene?
    menuScene = new QGraphicsScene();
    view = new GraphicsView();
    view->setScene(menuScene);
    keyManager = new KeyManager();
    audioManager = new AudioManager();

    level1 = new LevelManager(this, keyManager);

    view->setScene(level1->getScene());
    connectLevelManager();


    openMenu();
    level1->start();
    gameInProcess = true;
}

void GameManager::connectLevelManager()
{
    connect(level1, &LevelManager::signalGameOver, this, &GameManager::gameOver);
    connect(level1, &LevelManager::signalWin, this, &GameManager::win);
    connect(level1, &LevelManager::restartLevel, this, &GameManager::restartLevel);
}



void GameManager::gameOver(int score)
{
    if(gameWon){
        // if hero is hit by a bullet after the game is won, we do nothing.
        return;
    }
    gameInProcess = false;
    leaderBoardFile->update(getUserNameEntryBox(), score);
}

void GameManager::restartLevel()
{
   gameWon = false;
   delete level1;
   level1 = new LevelManager(this, keyManager);
   connectLevelManager();
   view->setScene(level1->getScene());
   openMenu();
   level1->start();
   gameInProcess = true;
}

void GameManager::openMenu()
{
    keyManager->releaseKeyboard();
    StartDialog *menu = new StartDialog();
    int mode = menu->exec();
    if (mode == menu->Mode::story){
        level1->setTotalEnemiesToKill(2);
    }
    else if (mode == menu->Mode::endless){
        level1->setTotalEnemiesToKill(INT_MAX);
    }
    else if (mode == menu->Mode::leaderBoard){
        createLeaderBoardBox();
        openMenu();
    }
    else if (mode == menu->Mode::quit){
        view->window()->close();
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);     //quit program
    }
    keyManager->grabKeyboard();
}

void GameManager::createLeaderBoardBox()
{
    LeaderBoardWindow* leaderBoardWin = new LeaderBoardWindow();
    leaderBoardWin->setLeaderboard(leaderBoardFile->load());
    leaderBoardWin->exec();
}

QString GameManager::getUserNameEntryBox()
{

    keyManager->releaseKeyboard();
    QString userName = "";
    bool ok;

    QString text = QInputDialog::getText(nullptr, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
        userName = text;
    keyManager->grabKeyboard();
    return userName;
}

void GameManager::win()
{
    gameWon = true;
    gameInProcess = false;

}

