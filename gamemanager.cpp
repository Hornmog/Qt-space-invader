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

    connect(keyManager, &KeyManager::keyRPressed, this, &GameManager::keyRPressed); 
}

void GameManager::createFullScreenImage(QString imagePath)
{
    if (imagePath != nullptr) {
        QPixmap pixmap(imagePath);
        fullScreenImage = new QGraphicsPixmapItem(pixmap.scaled(view->width(), view->height(), Qt::KeepAspectRatio));
    } else {
        fullScreenImage = new QGraphicsPixmapItem();
    }
    fullScreenImage->setPos(0, scene->height() / 2 - fullScreenImage->boundingRect().height() / 2);
    fullScreenImage->setZValue(ScenePriority::fullScreenText);
    scene->addItem(fullScreenImage);
}

void GameManager::gameOver()
{
    if(gameWon){
        return;
    }


    createEndScreen();
    gameInProcess = false;

    leaderBoardFile->update(getUserNameEntryBox(), scoreBar->score);
}

void GameManager::keyRPressed()
{
    if(!gameInProcess){
        restartLevel();
    }
}


void GameManager::restartLevel()
{
   gameWon = false;
   deleteSceneGraphicItems();
   if (enemyManager != nullptr){
       delete enemyManager;
   }
   // create new LevelManager
   if(clock->isPaused()){
       clock->resume(); //to unpause hero if restart was called during pause
   }
}

void GameManager::openMenu()
{
    StartDialog *menu = new StartDialog();
    int mode = menu->exec();
    if (mode == menu->Mode::story){
        enemyManager->setTotalEnemiesToKill(2);
    }
    else if (mode == menu->Mode::endless){
        enemyManager->setTotalEnemiesToKill(INT_MAX);
    }
    else if (mode == menu->Mode::leaderBoard){
        createLeaderBoardBox();
        openMenu();
    }
    else if (mode == menu->Mode::quit){
        view->window()->close();
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);     //quit program
    }
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
    createWinScreen();
    gameInProcess = false;
    delete enemyManager;
    enemyManager = nullptr;
}

void GameManager::createEndScreen()
{
    createFullScreenImage(ImagePaths::gameOver);
    QGraphicsTextItem* finalLabel = createTextItem();
    finalLabel->setPlainText("Press R To Open Menu");
    finalLabel->setPos(scene->width() / 2 - finalLabel->boundingRect().width() / 2,
                   scene->height() * 7 / 8 - finalLabel->boundingRect().height() / 2);
    scene->addItem(finalLabel);
}

void GameManager::createWinScreen()
{
    createFullScreenImage(ImagePaths::win);
}

