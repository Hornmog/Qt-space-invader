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
    speed = CoordPair(0,0);
    side = Side::hero;
    this->stop();

    setUpDelay(shootDelay);

    this->keyManager = keyManager;
    connect(keyManager, SIGNAL(heroKeyPressed(int)), this, SLOT(heroKeyPressed(int)));
    connect(keyManager, SIGNAL(heroKeyReleased(int)), this, SLOT(heroKeyReleased(int)));
    connect(keyManager, SIGNAL(logKeyPressed(bool)), this, SLOT(toggleCheckText(bool)));
}

void Hero::stop()
{
    bool checkTextVisibility = checkText->isVisible();
    active = false;
    mainTimer->stop();
    engineAccel.x = 0, speed.x = 0;
    this->hide();
    toggleCheckText(checkTextVisibility);
}

void Hero::start()
{
    bool checkTextVisibility = checkText->isVisible();
    active = true;
    mainTimer->start();
    this->show();
    toggleCheckText(checkTextVisibility);
}

void Hero::onTimer()
{
    groupCheckTextInfo();

    if(removalCheck() != Side::nobody){
        heroKilled();
    }
    else{       
        setPos(x() + calculateMovement('x'), y() + calculateMovement('y'));
    }

}

void Hero::groupCheckTextInfo()
{
    QString output = "";
    output += "Acceleration: " + QString::number(engineAccel.x) + "\n";
    output += "Speed: x: " + QString::number(speed.x) + " y: " + QString::number(speed.y) + "\n";
    setCheckText(output);
}

void Hero::heroKeyPressed(int key)
{
    if(!active) return;

    if (key == Qt::Key_Left && pos().x() > 0){
        engineAccel.x = -movement.engineAccel.x;
    }
    else if (key == Qt::Key_Right && pos().x() + this->boundingRect().width() < scene()->width()){
        engineAccel.x = movement.engineAccel.x;
    }
    else if (key == Qt::Key_Up && pos().y() > 0){
        engineAccel.y = -movement.engineAccel.y;
    }
    else if (key == Qt::Key_Down && pos().y() + this->boundingRect().height() < scene()->height()){
        engineAccel.y = movement.engineAccel.y;
    }
    if (arrowKeys.contains(key)) {
        keyPressed[key] = true;
        keyPressed[oppositeKey[key]] = false;
    }
    else if (key == Qt::Key_Space && shootAvl){
        createBullet(1);

        //qDebug() << shootAvl;
    }

}

void Hero::heroKeyReleased(int key)
{
    if(!active){
        return;
    }

    if(keyPressed[key]){
        engineAccel.x = 0;
        keyPressed[key] = false;
    }
}

int Hero::calculateMovement(char coord)
{
    int speedC = speed.get(coord);
    double newSpeed = 0;

    int direction;
    if (speedC == 0) direction = 0;
    else direction = abs(speedC) / speedC;

    if(engineAccel.get(coord) != 0){
        newSpeed = speedC + engineAccel.get(coord) * (float(period_ms)/1000);

    } else {
        newSpeed = newSpeed - movement.friction.get(coord) * (float(period_ms)/1000) * direction;
    }
    // newDirection == 0??
    int newDirection = abs(newSpeed) / newSpeed;

    if(engineAccel.get(coord) == 0 && direction != newDirection){
        newSpeed = 0;
        direction = newDirection;
    }

    if (abs(newSpeed) > movement.maxVelocity.get(coord)){
        newSpeed = movement.maxVelocity.get(coord) * direction;
    }

    float distanceMoved = 0.5 * (newSpeed + speedC) * (float(period_ms)/1000);

    speed.set(coord, newSpeed);

    if(checkScreenBorders(distanceMoved)){
        speed.set(coord, 0);
        return 0;
    }
    return distanceMoved;
}

bool Hero::checkScreenBorders(int distance)
{
    return ((pos().x() + this->width * 0.75 <= 0 && distance < 0) ||
             (pos().x() + this->width * 0.25 >= scene()->width() && distance > 0));
}

