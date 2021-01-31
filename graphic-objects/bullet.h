#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsRectItem>
#include <QObject>
#include "consts.h"
#include "gamemanager.h"
#include "animatedobject.h"

class Bullet: public AnimatedObject{
    Q_OBJECT
public:
    Bullet(float speed = 10, int side = 1, QString imagePath = "");  //add enum regarding side
    ~Bullet() override;

    void onHit();

    int getBulletLength() const {return bulletLength;}
    int getSpeed() const {return speed;}
    int type() const override {return TypeIndex::bullet;}

    int side;

public slots:
    void move();
private:
    static const int bulletLength = 50;
    static const int bulletWidth = 10;
    int speed;
};

#endif // BULLET_H
