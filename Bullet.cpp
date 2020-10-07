#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "Const.h"

Bullet::Bullet(int speed, const int type)
{    
    QString imagePath;
    if(type == 1){
         imagePath = ImagePaths::bulletImagePath;
    }
    else if(type == 2){
         imagePath = ImagePaths::enemyBulletImagePath;
    }


    QPixmap pixmap(imagePath);
    this->setPixmap(pixmap.scaled(bulletWidth,bulletLength));

    this->speed = speed;

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

Bullet::~Bullet() {
    qDebug() << "Bullet removed";
    scene()->removeItem(this);
}


void Bullet::move()
{
    setPos(x(),y() - speed);
    if((pos().y() + this->boundingRect().height() < 0)){
        delete this;                                         //when bullet leaves view, it is destroyed
    }
}

void Bullet::onHit() {
    delete this;
}
