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
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,sceneWidth,sceneHeight);

    view = new GraphicsView(scene);
    keyManager = new KeyManager();
    audioManager = new AudioManager();
    scoreBar = new ScoreBar();
    createBackground();   
    scene->addItem(scoreBar);
    scoreBar->setPos(scene->width() - scoreBar->boundingRect().width()*3, scene->height() - scoreBar->boundingRect().height());

    createFullScreenImage(nullptr);
    createPauseSceen();

    connect(keyManager, &KeyManager::keyRPressed, this, &GameManager::keyRPressed);
    connect(keyManager, &KeyManager::keyPPressed, this, &GameManager::togglePause);

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
}

void GameManager::gameOver()
{
    if(gameWon){
        return;
    }
    delete hero;
    hero = nullptr;

    delete enemyManager;
    enemyManager = nullptr;

    audioManager->stopBackground();

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
    if(gameInProcess && !clock->isPaused()){
        gameInProcess = false;
        clock->pause();
        hero->setActive(false);
        pause->show();
    }
    else if(!gameInProcess && clock->isPaused()){
        gameInProcess = true;
        clock->resume();
        hero->setActive(true);
        pause->hide();
    }
}

void GameManager::restartLevel()
{
   gameWon = false;
   deleteSceneGraphicItems();
   if (enemyManager != nullptr){
       delete enemyManager;
   }
   start();
   if(clock->isPaused()){
       clock->resume(); //to unpause hero if restart was called during pause
   }
}

void GameManager::start()
{
    keyManager->grabKeyboard();
    scoreBar->setScore(0);
    createPauseSceen();

    audioManager->playBackground();
    hero = new Hero(ImagePaths::hero, keyManager);

    hero->addToScene(scene);
    //scene->addItem(hero);

    qDebug() << "hero boundary: " << hero->boundingRect() ;
    enemyManager = new EnemyManager(scene, keyManager);

    connectSpaceshipSignals();
    openMenu();

    createCountdownTextItem();
    startLevelCountdown();

    gameInProcess = true;
    hero->setActive(true);
    hero->show();
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

QGraphicsTextItem* GameManager::createTextItem()
{
    QGraphicsTextItem* item = new QGraphicsTextItem();
    QFont font = QFont("Impact", 40, QFont::Bold);
    item->setFont(font);
    item->setDefaultTextColor(QColor(156, 20, 68));
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

void GameManager::createPauseSceen()
{
    pause = new QGraphicsPixmapItem();
    QPixmap pauseImage(ImagePaths::pause);
    pause->setPixmap(pauseImage.scaled(pauseWidth, pauseHeight));
    pause->setZValue(ScenePriority::pause);
    pause->hide();
    pause->setPos(scene->width()/2 - pauseWidth/2, scene->height()/2 - pauseHeight/2);
    scene->addItem(pause);
}

void GameManager::connectSpaceshipSignals()
{
    connect(enemyManager, &EnemyManager::onEnemyCountChange, this, &GameManager::changeScore);
    connect(enemyManager, &EnemyManager::allEnemiesDefeated, this, &GameManager::win);
    connect(hero, &Hero::heroKilled, this, &GameManager::gameOver);
    connect(enemyManager, &EnemyManager::enemyOnBase, this, &GameManager::gameOver);
}

void GameManager::deleteSceneGraphicItems()
{
    auto items = scene->items();  
    for (QGraphicsItem* item: qAsConst(items)) {
        if(!itemTypesToKeep.contains(item->type())){
            delete item;
        }
    }
}

void GameManager::createBackground()
{
    QPixmap pixmap(ImagePaths::background);
    QBrush pattern(pixmap);
    QRectF rect(0, 0, view->width(), view->height());
    scene->addRect(rect, QPen(), pattern);
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
    phase = 3;

    countdown = new Timer();
    connect(countdown, &QTimer::timeout, this, &GameManager::startLevelCountdown);
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
        delete countdown;
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

