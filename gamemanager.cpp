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
    KeyManager* keyManager = new KeyManager();
    enemyManager = new EnemyManager(scene, scoreBar, keyManager);
    hero = new Hero(ImagePaths::heroImagePath, keyManager);

    scoreBar = new ScoreBar();

    createBackground();

    scene->addItem(scoreBar);
    scoreBar->setPos(scene->width() - scoreBar->boundingRect().width()*3, scene->height() - scoreBar->boundingRect().height());

    scene->addItem(hero);


    connect(enemyManager, SIGNAL(onEnemyCountChange(int)), this, SLOT(changeScore(int)));
    connect(enemyManager, SIGNAL(allEnemiesDefeated()), this, SLOT(createWinScreen()));
    connect(hero, SIGNAL(heroKilled()), this, SLOT(gameOver()));
    connect(enemyManager, SIGNAL(enemyOnBase()), this, SLOT(gameOver()));

    keyManager->grabKeyboard();
    hero->setPos(view->width()/2 - hero->boundingRect().width()/2, view->height() - hero->boundingRect().height() * 2);

    createCountdownTextItem();
    startLevelCountdown();
}

void GameManager::createFullScreenImage(QString imagePath)
{
    QPixmap pixmap(imagePath);
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap.scaled(view->width(), view->height(), Qt::KeepAspectRatio));
    pixmapItem->setPos(0, scene->height() / 2 - pixmapItem->boundingRect().height() / 2);
    pixmapItem->setZValue(ScenePriority::fullScreenText);
    scene->addItem(pixmapItem);


}

void GameManager::gameOver()
{
    delete hero;
    createEndScreen();

}

void GameManager::createEndScreen()
{
    createFullScreenImage(ImagePaths::gameOverImagePath);
}

void GameManager::createWinScreen()
{
    createFullScreenImage(ImagePaths::winImagePath);
}

void GameManager::createBackground()
{
    QPixmap pixmap(backgroundImagePath);
    QBrush pattern(pixmap);
    qDebug() << pixmap;
    QRectF rect(0, 0, view->width(), view->height());
    scene->addRect(rect, QPen(), pattern);
}

void GameManager::startEnemySpawn()
{
    enemyManager->startSpawningEnemies();
}

void GameManager::createCountdownTextItem()
{
    number = new QGraphicsTextItem();
    QFont font = QFont("Impact", 40, QFont::Bold);
    QColor color = QColor("#9C1444");
    number->setFont(font);
    number->setDefaultTextColor(color);
    number->setZValue(ScenePriority::text);
    number->setPos(scene->width() / 2 - number->boundingRect().width() / 2,
                   scene->height() / 2 - number->boundingRect().height() / 2);
    scene->addItem(number);

}

void GameManager::startLevelCountdown()
{
    qDebug() << "Current phase is: " << phase;
    if (phase == -1) {
        number->hide();
        startEnemySpawn();
        return;
    }
    number->setPlainText(countdownPhrases[phase]);
    number->setPos(scene->width() / 2 - number->boundingRect().width() / 2,
                   scene->height() / 2 - number->boundingRect().height() / 2);
    phase--;

    QTimer* countdown = new QTimer();
    connect(countdown,SIGNAL(timeout()),this,SLOT(startLevelCountdown()));
    countdown->setSingleShot(true);
    countdown->start(1000);
}


void GameManager::changeScore(int score)
{
    scoreBar->setScore(score);
}

