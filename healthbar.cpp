#include "healthbar.h"
#include "consts.h"

HealthBar::HealthBar(QObject *parent, QGraphicsScene* scene) : QObject(parent)
{
    this->scene = scene;
}

void HealthBar::setLives(int value)
{
    if(value < 0){
        return;
    }

    int prevLives = lives;
    lives = value;

    if(prevLives > lives){
        removeLives(prevLives - lives);
    }
    else if(prevLives < lives){
        addLives(lives - prevLives);
    }
}

void HealthBar::removeLives(int value)
{
    for(int i= 0; i < value; i++){
        scene->removeItem(lifeList.last());
        delete lifeList.last();
        lifeList.pop_back();
    }
}

void HealthBar::addLives(int value)
{
    for(int i= 0; i < value; i++){
        lifeList.push_back(createHeart(i));
    }
}

QGraphicsPixmapItem *HealthBar::createHeart(int i)
{
    QPixmap* heartImage = new QPixmap(ImagePaths::heart);
    auto heart = new QGraphicsPixmapItem(heartImage->scaled(heartWidth, heartHeight));
    scene->addItem(heart);
    heart->setPos(sceneWidth - (lifeList.size() + i + 1) * (heartWidth + heartOffset), heartOffset);
    return heart;
}
