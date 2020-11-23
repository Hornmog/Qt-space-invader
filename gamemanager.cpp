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

GameManager::GameManager(QObject *parent) : QObject(parent)
{       
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,sceneWidth,sceneHeight);

    view = new GraphicsView(scene);
    keyManager = new KeyManager();
    scoreBar = new ScoreBar();
    createBackground();   
    scene->addItem(scoreBar);
    scoreBar->setPos(scene->width() - scoreBar->boundingRect().width()*3, scene->height() - scoreBar->boundingRect().height());

    createFullScreenImage(nullptr);

    connect(keyManager, SIGNAL(keyRPressed()), this, SLOT(keyRPressed()));
    connect(keyManager, SIGNAL(keyPPressed()), this, SLOT(togglePause()));
    connect(countdown,SIGNAL(timeout()),this,SLOT(startLevelCountdown()));

    createCountdownTextItem();
    start();
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
    qDebug() << fullScreenImage->type() << " - fullScreen image type";

}

void GameManager::gameOver()
{
    delete hero;
    hero = nullptr;
    delete enemyManager;
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

void GameManager::togglePause()
{
    if(!pause && gameInProcess){
        gameInProcess = false;
        hero->pause();
        enemyManager->pause();
    }
    else if(pause && !gameInProcess){
        gameInProcess = true;
        hero->resume();
        enemyManager->resume();
    }
}

void GameManager::restartLevel()
{
   deleteSceneGraphicItems();
   start();
}

void GameManager::start()
{
    keyManager->grabKeyboard();
    scoreBar->setScore(0);

    if (hero == nullptr){
        qDebug() << "creating new hero...";
        hero = new Hero(ImagePaths::heroImagePath, keyManager);
        scene->addItem(hero);
    } else {
        qDebug() << "hero exists";
    }

    hero->setPos(view->width()/2 - hero->boundingRect().width()/2, view->height() - hero->boundingRect().height() * 2);
    enemyManager = new EnemyManager(scene, keyManager);

    connectSpaceshipSignals();
    setMode(enemyManager);

    createCountdownTextItem();
    startLevelCountdown();

    gameInProcess = true;
    hero->resume();
    hero->show();
}

void GameManager::setMode(EnemyManager *enemyManager)
{
    StartDialog *chooseMode = new StartDialog();
    int mode = chooseMode->exec();
    if (mode == chooseMode->Mode::story){
        enemyManager->setTotalEnemiesToKill(5);
    }
    else if (mode == chooseMode->Mode::endless){
        enemyManager->setTotalEnemiesToKill(INT_MAX);
    }
    else if (mode == chooseMode->Mode::leaderBoard){
        createLeaderBoardBox();
        setMode(enemyManager);
    }
    else if (mode == chooseMode->Mode::quit){
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

QGraphicsTextItem* GameManager::createTextItem()
{
    QGraphicsTextItem* item = new QGraphicsTextItem();
    QFont font = QFont("Impact", 40, QFont::Bold);
    QColor color = QColor("#9C1444");
    item->setFont(font);
    item->setDefaultTextColor(color);
    item->setZValue(ScenePriority::text);
    return item;
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
    createWinScreen();
    gameInProcess = false;
    delete enemyManager;
}

void GameManager::createEndScreen()
{
    createFullScreenImage(ImagePaths::gameOverImagePath);
    QGraphicsTextItem* finalLabel = createTextItem();
    finalLabel->setPlainText("Press R To Open Menu");
    finalLabel->setPos(scene->width() / 2 - finalLabel->boundingRect().width() / 2,
                   scene->height() * 7 / 8 - finalLabel->boundingRect().height() / 2);
    qDebug() << "final label type: " << finalLabel->type();
    scene->addItem(finalLabel);
}

void GameManager::createWinScreen()
{
    createFullScreenImage(ImagePaths::winImagePath);
}

void GameManager::connectSpaceshipSignals()
{
    connect(enemyManager, SIGNAL(onEnemyCountChange(int)), this, SLOT(changeScore(int)));
    connect(enemyManager, SIGNAL(allEnemiesDefeated()), this, SLOT(win()));
    connect(hero, SIGNAL(heroKilled()), this, SLOT(gameOver()));
    connect(enemyManager, SIGNAL(enemyOnBase()), this, SLOT(gameOver()));
}

void GameManager::deleteSceneGraphicItems()
{
    auto items = scene->items();
    for (QGraphicsItem* item: items) {
        if(!itemTypesToKeep.contains(item->type())){
            delete item;
        }
    }
}

void GameManager::createBackground()
{
    QPixmap pixmap(backgroundImagePath);
    QBrush pattern(pixmap);
    qDebug() << pixmap;
    QRectF rect(0, 0, view->width(), view->height());
    QGraphicsItem* rectItem = scene->addRect(rect, QPen(), pattern);
    qDebug() << rectItem->type();
}

void GameManager::startEnemySpawn()
{
    enemyManager->startSpawningEnemies();
}

void GameManager::createCountdownTextItem()
{
    qDebug() << "countdown created";
    number = createTextItem();
    number->setPos(scene->width() / 2 - number->boundingRect().width() / 2,
                   scene->height() / 2 - number->boundingRect().height() / 2);
    scene->addItem(number);   
}

void GameManager::startLevelCountdown()
{
    if (phase == 3) {
        number->show();
    }
    qDebug() << "Current phase is: " << phase;
    if (phase == -1) {
        phase = 3;
        number->hide();
        startEnemySpawn();
        return;
    }
    number->setPlainText(countdownPhrases[phase]);
    number->setPos(scene->width() / 2 - number->boundingRect().width() / 2,
                   scene->height() / 2 - number->boundingRect().height() / 2);
    phase--;

    countdown->setSingleShot(true);
    countdown->start(1000);
}



void GameManager::changeScore(int score)
{
    scoreBar->setScore(score);
}

