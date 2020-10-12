#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QGraphicsObject>
#include "spaceship.h"

class Hero: public SpaceShip{
    Q_OBJECT
public:
    Hero(QString imagePath = nullptr);
    void onHeroKey(QKeyEvent * event) override;

signals:
    void heroKilled();
public slots:
    void onTimer() override;
private:

};

#endif // MYRECT_H
