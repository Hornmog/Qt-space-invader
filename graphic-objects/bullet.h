#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsRectItem>
#include <QObject>
#include "consts.h"
#include "gamemanager.h"
#include "animatedobject.h"

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(float speed = 10, Side side = Side::hero);  //add enum regarding side
    ~Bullet() override;

    void deleteSelf();

    int getBulletLength() const {return bulletLength;}
    int getSpeed() const {return speed;}
    int type() const override {return TypeIndex::bullet;}

    int side;

public slots:
    void move();
private:
    Animator *animator;
    static const int bulletLength = 50;
    static const int bulletWidth = 20;
    int speed;
    static QString getPath(Side side);
};

#endif // BULLET_H
