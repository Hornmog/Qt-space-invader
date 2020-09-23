#include "enemymanager.h"
#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>

EnemyManager::EnemyManager(QGraphicsScene *scene)
{
    this->scene = scene;

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));

    timer->start(1000);
}

void EnemyManager::onEnemyRemoval(Enemy *enemy)
{
    enemyCount--;
}

void EnemyManager::onTimer()
{
    if(enemyCount < 3){
        createEnemy();
    }

}

void EnemyManager::createEnemy()
{
    Enemy * enemy = new Enemy(this);
    enemy->setRect(0,0,100,100);
    scene->addItem(enemy);
    enemy->setPos(0,0);
    enemyCount++;

}
