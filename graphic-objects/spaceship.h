#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "keymanager.h"
#include "consts.h"
#include "timer.h"
#include "coordpair.h"
#include "checktext.h"
#include "animatedobject.h"

class SpaceShip : public AnimatedObject
{
    Q_OBJECT
public:
    explicit SpaceShip(QObject *parent = nullptr, QString imagePath = nullptr);
    ~SpaceShip() override;
    virtual void addToScene(QGraphicsScene* scene);
    int side;
    static bool checkTextVisible;

public slots:
    virtual void onTimer() = 0;
    void toggleCheckText();

signals:

protected:
    QGraphicsItem* collisionCheck(int typeIndex);
    void createBullet(int side = 1);
    int bulletCollisionCheck();

    void setUpDelay(int delay);
    void setUpCheckText();
    void setCheckText(QString string);

    virtual void groupCheckTextInfo() = 0;

    CoordPair speed = CoordPair(0,0);
    CoordPair prevSpeed = CoordPair(0,0);
    int bulletSpeed;
    int shootDelay;
    const int baseShootDelay = 5000;
    bool shootAvl = true;
    CheckText *checkText;
    Timer* mainTimer;

private:
    Timer* timerBullet = nullptr;
    bool checkTextOnScene = false;

private slots:
    void shootIsAvl();
};

#endif // SPACESHIP_H
