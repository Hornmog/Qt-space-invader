#include "gamemanager.h"
#include <QGraphicsScene>
#include "hero.h"
#include <QGraphicsView>
#include "enemy.h"
#include "enemymanager.h"
#include "ScoreBar.h"
#include "graphicsview.h"


GameManager::GameManager(QObject *parent) : QObject(parent)
{

    scene = new QGraphicsScene();
    GraphicsView* view = new GraphicsView(scene);
    hero = new Hero();
    EnemyManager* enemyManager = new EnemyManager(scene,scoreBar);
    scoreBar = new ScoreBar();

    scene->addItem(hero);
    scene->addItem(scoreBar);
    scene->setSceneRect(0,0,800,600);
    scoreBar->setPos(750,500);

    connect(enemyManager, SIGNAL(onEnemyCountChange(int)), this, SLOT(changeScore(int)));
    connect(hero, SIGNAL(heroKilled()), this, SLOT(gameOver()));

    hero->grabKeyboard();
    hero->setPos(view->width()/2 - hero->rect().width()/2, view->height() - hero->rect().height());
}

void GameManager::gameOver()
{
    delete hero;
    createEndScreen();

}

void GameManager::createEndScreen()
{
    QPixmap pixmapItem(imagePath);
    scene->addPixmap(pixmapItem);
    QPixmap pixmapItems = pixmapItem.scaled(QSize(24,24),  Qt::KeepAspectRatio);
}

void GameManager::changeScore(int score)
{
    scoreBar->setScore(score);
}
