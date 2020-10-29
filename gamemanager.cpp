#include "gamemanager.h"
#include <QGraphicsScene>
#include "graphic-objects/hero.h"
#include <QGraphicsView>
#include "graphic-objects/enemy.h"
#include "enemymanager.h"
#include "scorebar.h"
#include "graphicsview.h"
#include <QDebug>
#include "consts.h"
#include <QTimer>


GameManager::GameManager(QObject *parent) : QObject(parent)
{

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,sceneWidth,sceneHeight);

    view = new GraphicsView(scene);
    keyManager = new KeyManager();
    enemyManager = new EnemyManager(scene, scoreBar, keyManager);
    hero = new Hero(ImagePaths::heroImagePath, keyManager);
    hero->setPos(view->width()/2 - hero->boundingRect().width()/2, view->height() - hero->boundingRect().height() * 2);

    scoreBar = new ScoreBar();

    createBackground();

    scene->addItem(scoreBar);
    scoreBar->setPos(scene->width() - scoreBar->boundingRect().width()*3, scene->height() - scoreBar->boundingRect().height());

    scene->addItem(hero);
    createFullScreenImage(nullptr);

    keyManager->grabKeyboard();

    connectSpaceshipSignals();
    connect(keyManager, SIGNAL(keyRPressed()), this, SLOT(keyRPressed()));
    connect(countdown,SIGNAL(timeout()),this,SLOT(startLevelCountdown()));

    createCountdownTextItem();
    startLevelCountdown();
    gameInProcess = true;
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
}

void GameManager::keyRPressed()
{
    if(!gameInProcess){
        restartLevel();
    }
}

void GameManager::restartLevel()
{
   deleteSceneGraphicItems();
   gameInProcess = true;
   scoreBar->setScore(0);

   if (hero == nullptr){
       qDebug() << "creating new hero...";
       hero = new Hero(ImagePaths::heroImagePath, keyManager);
       scene->addItem(hero);
   }

   hero->setPos(view->width()/2 - hero->boundingRect().width()/2, view->height() - hero->boundingRect().height() * 2);
   enemyManager = new EnemyManager(scene, scoreBar, keyManager);
   connectSpaceshipSignals();
   startLevelCountdown();
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
        if(itemTypesToDelete.contains(item->type())){
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
    number = new QGraphicsTextItem();
    QFont font = QFont("Impact", 40, QFont::Bold);
    QColor color = QColor("#9C1444");
    number->setFont(font);
    number->setDefaultTextColor(color);
    number->setZValue(ScenePriority::text);
    number->setPos(scene->width() / 2 - number->boundingRect().width() / 2,
                   scene->height() / 2 - number->boundingRect().height() / 2);
    scene->addItem(number);   
    qDebug() << "number created: " << number;
    qDebug() << number->type() << " - number type";
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

