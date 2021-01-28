#include "levelmanager.h"
#include "consts.h"
#include "soundeffect.h"

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
        emit restartLevel();
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
    connect(countdown, &QTimer::timeout, this, countDownX);
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
    connect(countdown, &QTimer::timeout, this, countDownX);

    countdown->setSingleShot(true);
    countdown->start(1000);
}

void LevelManager::changeScore(int score)
{
    scoreBar->setScore(score);
}

void LevelManager::createScreenImage(QString imagePath)
{
    QPixmap pixmap(imagePath);

    QGraphicsPixmapItem* fullScreenImage = new QGraphicsPixmapItem(
                pixmap.scaled(sceneWidth, sceneHeight, Qt::KeepAspectRatio));
    fullScreenImage->setPos(0, sceneHeight / 2 - fullScreenImage->boundingRect().height() / 2);
    fullScreenImage->setZValue(ScenePriority::fullScreenText);
    scene->addItem(fullScreenImage);
}

void LevelManager::createPressRImage()
{
    // This function is basically identical with the one above.
    // Consider fusing them, maybe by introducing additional parameters
    QPixmap pressRPixmap(ImagePaths::pressR);
    QGraphicsPixmapItem* pressRImage = new QGraphicsPixmapItem(
                pressRPixmap.scaled(sceneWidth/2, sceneHeight, Qt::KeepAspectRatio));

    pressRImage->setPos(sceneWidth/4, sceneHeight - pressRImage->boundingRect().height() * 3);
    pressRImage->setZValue(ScenePriority::fullScreenText);
    scene->addItem(pressRImage);
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
    createPressRImage();

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
