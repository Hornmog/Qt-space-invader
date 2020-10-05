#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsRectItem>
#include <QObject>
#include "Cons.h"

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(int speed = 10, const int type = 1);  //1-Regular ---  2-Enemy ---  Pixmap
    ~Bullet();
    int type() const override{
        return Keys::bulletIndex;
    }
    bool removalCheck();
    void onHit();

    int getBulletLength() const {return bulletLength;}
    int getSpeed() const {return speed;}

public slots:
    void move();
private:
    const int bulletLength = 50;
    const int bulletWidth = 10;
    int speed;
};

#endif // BULLET_H
