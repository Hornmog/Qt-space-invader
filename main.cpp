 #include <QApplication>
#include <QGraphicsScene>
#include "hero.h"
#include <QGraphicsView>
#include "enemy.h"
#include "enemymanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene * scene = new QGraphicsScene();

    Hero * player = new Hero();
    player->setRect(0,0,100,100);
    scene->addItem(player);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    EnemyManager * enemyManager = new EnemyManager(scene);

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
