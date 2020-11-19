#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsRectItem>
#include <QObject>
#include "consts.h"
#include "gamemanager.h"

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(int speed = 10, int side = 1);  //add enum regarding side
    ~Bullet() override;

    void onHit();

    int getBulletLength() const {return bulletLength;}
    int getSpeed() const {return speed;}
    int type() const override {return TypeIndex::bullet;}

    int side;

public slots:
    void move();
private:
    static GameManager* gameManager;
    static const int bulletLength = 50;
    static const int bulletWidth = 10;
    int speed;
};

#endif // BULLET_H
