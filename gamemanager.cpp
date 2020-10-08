#include "gamemanager.h"
#include <QGraphicsScene>
#include "hero.h"
#include <QGraphicsView>
#include "enemy.h"
#include "enemymanager.h"
#include "ScoreBar.h"
#include "graphicsview.h"
#include <QDebug>
#include "Const.h"


GameManager::GameManager(QObject *parent) : QObject(parent)
{

    scene = new QGraphicsScene();
    view = new GraphicsView(scene);
    hero = new Hero(ImagePaths::heroImagePath);
    EnemyManager* enemyManager = new EnemyManager(scene,scoreBar);
    scoreBar = new ScoreBar();


    scene->setSceneRect(0,0,sceneWidth,sceneHeight);
    createBackground();
    scene->addItem(scoreBar);
    scene->addItem(hero);
    scoreBar->setPos(750,500);

    connect(enemyManager, SIGNAL(onEnemyCountChange(int)), this, SLOT(changeScore(int)));
    connect(enemyManager, SIGNAL(allEnemiesDefeated()), this, SLOT(createWinScreen()));
    connect(hero, SIGNAL(heroKilled()), this, SLOT(gameOver()));

    hero->grabKeyboard();
    hero->setPos(view->width()/2 - hero->boundingRect().width()/2, view->height() - hero->boundingRect().height());
}

void GameManager::createFullScreenImage(QString imagePath)
{
    QPixmap pixmap(imagePath);
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap.scaled(view->width(), view->height()));
    pixmapItem->setPos(0,0);
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
    QRectF rect(0, 0, view->width(), view->height());
    scene->addRect(rect, QPen(), pattern);
}


void GameManager::changeScore(int score)
{
    scoreBar->setScore(score);
}

