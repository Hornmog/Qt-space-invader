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

    QGraphicsScene* scene = new QGraphicsScene();
    GraphicsView* view = new GraphicsView(scene);
    Hero* player = new Hero();
    EnemyManager* enemyManager = new EnemyManager(scene,scoreBar);
    scoreBar = new ScoreBar();

    scene->addItem(player);
    scene->addItem(scoreBar);
    scene->setSceneRect(0,0,800,600);
    scoreBar->setPos(750,500);

    connect(enemyManager, SIGNAL(onEnemyCountChange(int)), this, SLOT(changeScore(int)));

    player->grabKeyboard();
    player->setPos(view->width()/2 - player->rect().width()/2, view->height() - player->rect().height());
}

void GameManager::changeScore(int score)
{
    scoreBar->setScore(score);
}
