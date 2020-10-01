#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QGraphicsObject>
#include "spaceship.h"

class Hero: public SpaceShip{
    Q_OBJECT
public:
    Hero();
    void keyPressEvent(QKeyEvent * event) override;

signals:
    void heroKilled();
public slots:
    void onTimer() override;
};

#endif // MYRECT_H
