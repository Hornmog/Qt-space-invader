#include "hero.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include "bullet.h"
#include <QTimer>
#include "keymanager.h"

Hero::Hero(QString imagePath, KeyManager* keyManager) : SpaceShip(nullptr, imagePath)
{
    shootDelay = 1000;
    bulletSpeed = 10;
    xSpeed = 10;     //Speed is a step with which hero moves upon keyPressEvent
    ySpeed = 10;
    xVelocity = 0;
    accelNumberOfCycles =  MovementX::accelTime / onTimerPeriod;
    accelCyclesLeft = accelNumberOfCycles;
    accel = 0;
    side = Side::hero;


    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    //this->setFocus();

    setUpDelay(shootDelay);

    this->keyManager = keyManager;
    connect(keyManager, SIGNAL(heroKeyPressed(int)), this, SLOT(heroKeyPressed(int)));
    connect(keyManager, SIGNAL(logKeyPressed(bool)), this, SLOT(toggleCheckText(bool)));
}

void Hero::onTimer()
{
    groupCheckTextInfo();

    if(removalCheck() != Side::nobody){
        heroKilled();
    }
    else{
        setPos(x() + calculateXMovement(), y());
    }

}

void Hero::groupCheckTextInfo()
{
    QString output = "";
    output += "Acceleration: " + QString::number(accel) + "\n";
    output += "Speed: x: " + QString::number(xSpeed) + " y: " + QString::number(ySpeed) + "\n";
    setCheckText(output);
}

void Hero::heroKeyPressed(int key)
{
    //qDebug() << "key pressed";
    if (key == Qt::Key_Left){
        if(pos().x() > 0){
            accel = -MovementX::accel;
            //setPos(x()-xSpeed,y());
        }
    }
    else if (key == Qt::Key_Right){
        if(pos().x() + this->boundingRect().width() < scene()->width()){
            accel = MovementX::accel;
            //setPos(x()+xSpeed,y());
        }
    }
    else if (key == Qt::Key_Up){
        if(pos().y() > 0){
            setPos(x(), y() - ySpeed);
        }
    }
    else if (key == Qt::Key_Down){
        if(pos().y() + this->boundingRect().height() < scene()->height()){
            setPos(x(), y() + ySpeed);
        }
    }

    else if (key == Qt::Key_Space && shootAvl){
        createBullet(1);

        //qDebug() << shootAvl;
    }

}

int Hero::calculateXMovement()
{
    accelCyclesLeft--;

    if(accelCyclesLeft < 0){
        accel = 0;
        accelCyclesLeft = accelNumberOfCycles;
    }

    float newXVelocity = xVelocity + accel * (float(onTimerPeriod)/1000);

    if (abs(newXVelocity) > MovementX::maxVelocity){
        newXVelocity = MovementX::maxVelocity * abs(newXVelocity) / newXVelocity;
    }

    float distanceMoved = 0.5 * (newXVelocity + xVelocity) * (float(onTimerPeriod)/1000);

//    if(newXVelocity != 0){
//        newXVelocity = newXVelocity - Movement::heroXFriction * (float(onTimerPeriod)/1000);

//    }

    xVelocity = newXVelocity;
    return distanceMoved;
}

