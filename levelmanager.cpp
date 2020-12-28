#include "levelmanager.h"
#include "consts.h"
LevelManager::LevelManager(QObject *parent, KeyManager* keyManager) : QObject(parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,sceneWidth,sceneHeight);
    keyManager->grabKeyboard();

    scoreBar = new ScoreBar();
    scoreBar->setScore(0);
    audioManager = new AudioManager();
    createBackground();

    hero = new Hero(ImagePaths::hero, keyManager);
    hero->addToScene(scene);
    enemyManager = new EnemyManager(scene, keyManager);

    scene->addItem(scoreBar);
    scoreBar->setPos(scene->width() - scoreBar->boundingRect().width()*3, scene->height() - scoreBar->boundingRect().height());

    createPauseSceen();

    connect(keyManager, &KeyManager::keyPPressed, this, &LevelManager::togglePause);
    connectSpaceshipSignals();
    createCountdownTextItem();
    //start();
}

LevelManager::~LevelManager()
{
    audioManager->stopBackground();
}

void LevelManager::setTotalEnemiesToKill(int num)
{
    enemyManager->setTotalEnemiesToKill(num);
}

QGraphicsScene* LevelManager::getScene()
{
    return this->scene;
}



void LevelManager::start()
{
    //keyManager->grabKeyboard();

    audioManager->playBackground();
    startLevelCountdown();

    clock->start();

    gameInProcess = true;
    hero->setActive(true);
    hero->show();
}


void LevelManager::connectSpaceshipSignals()
{
    connect(enemyManager, &EnemyManager::onEnemyCountChange, this, &LevelManager::changeScore);
    connect(enemyManager, &EnemyManager::allEnemiesDefeated, this, &LevelManager::win);
    connect(hero, &Hero::heroKilled, this, &LevelManager::gameOver);
    connect(enemyManager, &EnemyManager::enemyOnBase, this, &LevelManager::gameOver);
}

/*void LevelManager::deleteSceneGraphicItems()
{
    auto items = scene->items();
    for (QGraphicsItem* item: qAsConst(items)) {
        if(!itemTypesToKeep.contains(item->type())){
            delete item;
        }
    }
}*/

void LevelManager::startEnemySpawn()
{
    enemyManager->startSpawningEnemies();
}

void LevelManager::togglePause()
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

void LevelManager::createPauseSceen()
{
    pause = new QGraphicsPixmapItem();
    QPixmap pauseImage(ImagePaths::pause);
    pause->setPixmap(pauseImage.scaled(pauseWidth, pauseHeight));
    pause->setZValue(ScenePriority::pause);
    pause->hide();
    pause->setPos(scene->width()/2 - pauseWidth/2, scene->height()/2 - pauseHeight/2);
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
    //recreate Number or pass as argument?
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

void LevelManager::createFullScreenImage(QString imagePath)
{
    QGraphicsPixmapItem* fullScreenImage;

    QPixmap pixmap(imagePath);
    fullScreenImage = new QGraphicsPixmapItem(pixmap.scaled(sceneWidth, sceneHeight, Qt::KeepAspectRatio));

    fullScreenImage->setPos(0, sceneHeight / 2 - fullScreenImage->boundingRect().height() / 2);
    fullScreenImage->setZValue(ScenePriority::fullScreenText);
    scene->addItem(fullScreenImage);
}


void LevelManager::gameOver()
{
    if (gameWon){
        return;
    }
    delete hero;
    delete enemyManager;
    createFullScreenImage(ImagePaths::gameOver);

    audioManager->stopBackground();
    emit signalGameOver(scoreBar->score);
    //start gameOver music
}
void LevelManager::win()
{
    gameWon = true;
    createFullScreenImage(ImagePaths::win);
    gameInProcess = false;
    delete enemyManager;
    emit signalWin();
}
