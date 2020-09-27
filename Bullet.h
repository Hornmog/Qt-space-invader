#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsRectItem>
#include <QObject>
#include "Cons.h"

class Bullet: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Bullet();
    ~Bullet();
    int type() const override{
        return Keys::bulletIndex;
    }
    bool removalCheck();
    void onHit();
    int speed;

public slots:
    void move();
};

#endif // BULLET_H
