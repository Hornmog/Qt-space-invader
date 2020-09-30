#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsRectItem>

class SpaceShip : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit SpaceShip(QObject *parent = nullptr);
    bool removalCheck();
    void createBullet();


    int width;
    int height;
    int speed;
    int bulletSpeed;
    int shootDelay;
    bool shootAvl = true;


public slots:
    void shootIsAvl();

signals:

};

#endif // SPACESHIP_H
