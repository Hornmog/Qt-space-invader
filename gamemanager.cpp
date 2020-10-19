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


GameManager::GameManager(QObject *parent) : QObject(parent)
{

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,sceneWidth,sceneHeight);

    view = new GraphicsView(scene);
    KeyManager* keyManager = new KeyManager();
    EnemyManager* enemyManager = new EnemyManager(scene, scoreBar, keyManager);
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
    qDebug() << "Background created";
    qDebug() << backgroundImagePath;
    QPixmap pixmap(backgroundImagePath);
    QBrush pattern(pixmap);
    qDebug() << pixmap;
    QRectF rect(0, 0, view->width(), view->height());
    scene->addRect(rect, QPen(), pattern);
}


void GameManager::changeScore(int score)
{
    scoreBar->setScore(score);
}

