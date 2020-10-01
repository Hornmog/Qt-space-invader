#include "gamemanager.h"
#include <QGraphicsScene>
#include "hero.h"
#include <QGraphicsView>
#include "enemy.h"
#include "enemymanager.h"
#include "ScoreBar.h"
#include "graphicsview.h"
#include <QDebug>


GameManager::GameManager(QObject *parent) : QObject(parent)
{

    scene = new QGraphicsScene();
    GraphicsView* view = new GraphicsView(scene);
    hero = new Hero();
    EnemyManager* enemyManager = new EnemyManager(scene,scoreBar);
    scoreBar = new ScoreBar();

    createBackground();
    scene->addItem(hero);
    scene->addItem(scoreBar);
    scene->setSceneRect(0,0,sceneWidth,sceneHeight);
    scoreBar->setPos(750,500);

    connect(enemyManager, SIGNAL(onEnemyCountChange(int)), this, SLOT(changeScore(int)));
    connect(hero, SIGNAL(heroKilled()), this, SLOT(gameOver()));

    hero->grabKeyboard();
    hero->setPos(view->width()/2 - hero->boundingRect().width()/2, view->height() - hero->boundingRect().height());
}

void GameManager::gameOver()
{
    delete hero;
    createEndScreen();

}

void GameManager::createEndScreen()
{
    QPixmap gameOverPixmap(gameOverImagePath);
    QGraphicsPixmapItem* gameOverItem = new QGraphicsPixmapItem(gameOverPixmap);
    scene->addItem(gameOverItem);

    gameOverItem->setPos(scene->width()/2 - gameOverItem->boundingRect().width()/2,
                         scene->height()/2 - gameOverItem->boundingRect().height()/2);
}

void GameManager::changeScore(int score)
{
    scoreBar->setScore(score);
}

void GameManager::createBackground()
{
    qDebug() << "create background";
    QPixmap Pixmap(backgroundImagePath);
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(Pixmap.scaled(sceneWidth,sceneHeight));

    scene->addItem(background);
    background->setPos(0,0);
}
