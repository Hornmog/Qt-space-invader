#include "levelmanager.h"
#include "consts.h"
#include "soundeffect.h"
#include <QMessageBox>
LevelManager::LevelManager(QObject *parent, KeyManager* keyManager) : QObject(parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,sceneWidth,sceneHeight);
    createBackground();

    scoreBar = new ScoreBar();
    scoreBar->setScore(0);
    scene->addItem(scoreBar);
    scoreBar->setPos(scene->width() - scoreBar->boundingRect().width()*3,
                     scene->height() - scoreBar->boundingRect().height());

    enemyManager = new EnemyManager(scene, keyManager);
    audioManager = new AudioManager();

    hero = new Hero(ImagePaths::hero, keyManager);
    hero->addToScene(scene);

    createPauseScreen();

    connect(keyManager, &KeyManager::keyPPressed, this, &LevelManager::togglePause);
    connect(keyManager, &KeyManager::keyRPressed, this, &LevelManager::checkRestart);
    connectSpaceshipSignals();
    createCountdownTextItem();
    keyManager->grabKeyboard();
}

LevelManager::~LevelManager()
{
    audioManager->stopBackground();
    if(gameWon){
        delete hero;
    }
    delete enemyManager;
}

void LevelManager::setTotalEnemiesToKill(int num)
{
    enemyManager->setTotalEnemiesToKill(num);
}

void LevelManager::checkRestart()
{
    if(!gameInProcess){
        if(requestRestartConfirmation()){
            emit restartLevel();
        }
        else{
            qDebug() << "restart cancelled";
        }
    }
}

void LevelManager::start()
{
    gameInProcess = true;
    clock->start();
    audioManager->playBackground();

    hero->setActive(true);
    hero->show();

    startLevelCountdown();
}


void LevelManager::connectSpaceshipSignals()
{
    connect(enemyManager, &EnemyManager::onEnemyCountChange, this, &LevelManager::changeScore);
    connect(enemyManager, &EnemyManager::allEnemiesDefeated, this, &LevelManager::win);
    connect(hero, &Hero::heroKilled, this, &LevelManager::lose);
    connect(enemyManager, &EnemyManager::enemyOnBase, this, &LevelManager::lose);
}

void LevelManager::startEnemySpawn()
{
    enemyManager->startSpawningEnemies();
}

void LevelManager::togglePause()
{
    if(gameInProcess && !clock->getClock()->isPaused()){
        gameInProcess = false;
        clock->pause();
        hero->setActive(false);
        pause->show();
    }
    else if(!gameInProcess && clock->getClock()->isPaused()){
        gameInProcess = true;
        clock->resume();
        hero->setActive(true);
        pause->hide();
    }
    else{
        qDebug() << "gameInProcess: " + QString(gameInProcess) + " clockPaused: " + QString(clock->getClock()->isPaused());
        throw std::domain_error("");
    }

}

void LevelManager::createPauseScreen()
{
    pause = new QGraphicsPixmapItem();
    QPixmap pauseImage(ImagePaths::pause);
    pause->setPixmap(pauseImage.scaled(pauseWidth, pauseHeight));
    pause->setZValue(ScenePriority::pause);
    pause->setPos(scene->width()/2 - pauseWidth/2, scene->height()/2 - pauseHeight/2);
    pause->hide();
    scene->addItem(pause);
}

bool LevelManager::requestRestartConfirmation()
{
      QMessageBox::StandardButton reply;
      reply = QMessageBox::question(nullptr, "Confirmation", "Are you sure you want to restart?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        return true;
      } else {
        qDebug() << "Yes was *not* clicked";
        return false;
      }
}


void LevelManager::createBackground()
{
    QPixmap pixmap(ImagePaths::background);
    QBrush pattern(pixmap);
    QRectF rect(0, 0, sceneWidth, sceneHeight);
    scene->addRect(rect, QPen(), pattern);
}

void LevelManager::createCountdownTextItem()
{
    qDebug() << "countdown created";
    number = UtilityFunctions::createTextItem();
    number->setPos(scene->width() / 2 - number->boundingRect().width() / 2,
                   scene->height() / 2 - number->boundingRect().height() / 2);
    scene->addItem(number);
    countdown = new Timer();
    auto countDownX = [=]() {startLevelCountdown(3);};
    connect(countdown, &Timer::timeout, this, countDownX);
}
void LevelManager::startLevelCountdown(int phase)
{
    if (phase == 3) {
        number->show();
    }
    qDebug() << "Current phase is: " << phase;
    if (phase == -1) {
        number->hide();
        startEnemySpawn();
        delete countdown;
        delete number;
        return;
    }
    number->setPlainText(countdownPhrases[phase]);
    number->setPos(scene->width() / 2 - number->boundingRect().width() / 2,
                   scene->height() / 2 - number->boundingRect().height() / 2);
    phase--;

    auto countDownX = [=]() {startLevelCountdown(phase);};
    disconnect(countdown, nullptr, nullptr, nullptr);
    connect(countdown, &Timer::timeout, this, countDownX);

    countdown->setSingleShot(true);
    countdown->start(1000);
}

void LevelManager::changeScore(int score)
{
    scoreBar->setScore(score);
}

void LevelManager::createScreenImage(QString imagePath, CoordPair scale, Position position)
{
    QPixmap pixmap(imagePath);

    QGraphicsPixmapItem* fullScreenImage = new QGraphicsPixmapItem(
                pixmap.scaled(scale.x, scale.y, Qt::KeepAspectRatio));

    switch(position){
    case middle:
        fullScreenImage->setPos(0, sceneHeight / 2 - fullScreenImage->boundingRect().height() / 2);
        break;
    case mid_up:
        fullScreenImage->setPos(0, sceneHeight / 4 - fullScreenImage->boundingRect().height() / 2);
        break;
    case mid_down:
        fullScreenImage->setPos(sceneWidth/4, sceneHeight - fullScreenImage->boundingRect().height() * 3);
        break;
    }

    fullScreenImage->setZValue(ScenePriority::fullScreenText);
    scene->addItem(fullScreenImage);
}

void LevelManager::lose()
{
    qDebug() << "lose!";
    if (!gameInProcess){
        // we can't lose a game that has been already won
        return;
    }
    gameInProcess = false;
    delete hero;

    createScreenImage(ImagePaths::gameOver);
    createScreenImage(ImagePaths::pressR, CoordPair(sceneWidth/2, sceneHeight), mid_down);

    audioManager->stopBackground();
    emit signalGameOver(scoreBar->score);
    //start gameOver music
}
void LevelManager::win()
{
    qDebug() << "win!";
    gameWon = true;
    gameInProcess = false;
    createScreenImage(ImagePaths::win);
    emit signalWin();

}
