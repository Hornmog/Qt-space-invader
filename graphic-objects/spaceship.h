#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsRectItem>
#include "keymanager.h"
#include "consts.h"
#include "timer.h"

class SpaceShip : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit SpaceShip(QObject *parent = nullptr, QString imagePath = nullptr);

    int side;
    const int width = 100;
    const int height = 100;

public slots:
    virtual void onTimer() = 0;
    void toggleCheckText(bool show);
    virtual void resume();
    virtual void pause();

signals:

protected:
    struct CoordPair {
        double x = 0;
        double y = 0;
        CoordPair(double x, double y) {
            this->x = x;
            this->y = y;
        }
        double get(char coord) const {
            if (coord == 'x') return x;
            else if (coord == 'y') return y;
            else return -1;
        }

        void set(char coord, int value) {
            if (coord == 'x') this->x = value;
            else if (coord == 'y') this->y = value;
        }
    };

    void createBullet(int side = 1);
    QGraphicsItem* collisionCheck(int typeIndex);
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
    QGraphicsTextItem *checkText;
    Timer* mainTimer;

private:
    Timer* timerBullet = nullptr;

private slots:
    void shootIsAvl();
};

#endif // SPACESHIP_H
