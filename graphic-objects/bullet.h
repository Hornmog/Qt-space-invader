#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsRectItem>
#include <QObject>
#include "consts.h"

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(int speed = 10, int side = 1);  //add enum regarding side
    ~Bullet() override;

    bool removalCheck();
    void onHit();

    int getBulletLength() const {return bulletLength;}
    int getSpeed() const {return speed;}
    int type() const override;

    int side;

public slots:
    void move();
private:
    const int bulletLength = 50;
    const int bulletWidth = 10;
    int speed;
};

#endif // BULLET_H
