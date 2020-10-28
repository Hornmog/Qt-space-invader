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
    bulletSpeed = 0.2 * period_ms; // 10 pixels per 50 ms
    ySpeed = 10;
    xSpeed = 0;
    accel = 0;
    side = Side::hero;

    setUpDelay(shootDelay);

    this->keyManager = keyManager;
    connect(keyManager, SIGNAL(heroKeyPressed(int)), this, SLOT(heroKeyPressed(int)));
    connect(keyManager, SIGNAL(heroKeyReleased(int)), this, SLOT(heroKeyReleased(int)));
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
            leftKeyPressed = true;
            rightKeyPressed = false;
        }
    }
    else if (key == Qt::Key_Right){
        if(pos().x() + this->boundingRect().width() < scene()->width()){
            accel = MovementX::accel;
            rightKeyPressed = true;
            leftKeyPressed = false;
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

void Hero::heroKeyReleased(int key)
{
    if(key == Qt::Key_Left && leftKeyPressed){
        accel = 0;
        leftKeyPressed = false;
    }
    if(key == Qt::Key_Right && rightKeyPressed){
        accel = 0;
        rightKeyPressed = false;
    }
}

int Hero::calculateXMovement()
{
    float newXVelocity = xSpeed + accel * (float(period_ms)/1000);

    if (abs(newXVelocity) > MovementX::maxVelocity){
        newXVelocity = MovementX::maxVelocity * abs(newXVelocity) / newXVelocity;
    }

    float distanceMoved = 0.5 * (newXVelocity + xSpeed) * (float(period_ms)/1000);

//    if(newXVelocity != 0){
//        newXVelocity = newXVelocity - Movement::heroXFriction * (float(onTimerPeriod)/1000);

//    }

    xSpeed = newXVelocity;

    if(checkScreenBorders(distanceMoved)){
        xSpeed = 0;
        return 0;
    }
    return distanceMoved;
}

bool Hero::checkScreenBorders(int distance)
{
    return ((pos().x() + this->width * 0.75 <= 0 && distance < 0) ||
             (pos().x() + this->width * 0.25 >= scene()->width() && distance > 0));
}

