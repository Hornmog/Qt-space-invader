#include "bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "consts.h"

Bullet::Bullet(int speed, int side)
{
    this->side = side;
    QString imagePath;
    if(side == 1){
         imagePath = ImagePaths::bulletImagePath;
    }
    else if(side == 2){
         imagePath = ImagePaths::enemyBulletImagePath;
    }

    QPixmap pixmap(imagePath);
    this->setPixmap(pixmap.scaled(bulletWidth,bulletLength));
    this->setZValue(ScenePriority::bullet);

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
    if((pos().y() + this->boundingRect().height() < 0 || pos().y() > scene()->height())){
        delete this;                                         //when bullet leaves view, it is destroyed
    }
}

void Bullet::onHit() {
    delete this;
}

int Bullet::type() const {
    return Keys::bulletIndex;
}
