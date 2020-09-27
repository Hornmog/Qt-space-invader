 #include <QApplication>
#include <QGraphicsScene>
#include "hero.h"
#include <QGraphicsView>
#include "enemy.h"
#include "enemymanager.h"
#include "ScoreBar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene * scene = new QGraphicsScene();

    //create Hero
    Hero * player = new Hero();
    scene->addItem(player);

    //create Score Bar
    ScoreBar *scoreBar = new ScoreBar();
    scene->addItem(scoreBar);
    scoreBar->setPos(750,500);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //create enemy manager
    EnemyManager * enemyManager = new EnemyManager(scene,scoreBar);

    QGraphicsView * view = new QGraphicsView(scene);

    //???
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
    view->setFixedSize(800,600);
    scene->setSceneRect(0,0,800,600);
    //resize window ?

    player->setPos(view->width()/2 - player->rect().width()/2, view->height() - player->rect().height());
    return a.exec();
}
