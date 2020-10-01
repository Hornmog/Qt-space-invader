#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>

Bullet::Bullet(int speed, const int type)
{    

    if(type == 1){
         ImagePath = ":/images/bullet.png";
    }
    else if(type == 2){
         ImagePath = ":/images/enemyBullet.png";
    }


    QPixmap Pixmap(ImagePath);
    this->setPixmap(Pixmap.scaled(bulletWidth,bulletLength));

    //setRect(0,0,10,bulletLength);
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
        delete this;
    }
}

void Bullet::onHit() {
    delete this;
}
