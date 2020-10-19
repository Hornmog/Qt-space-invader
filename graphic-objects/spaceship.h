#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsRectItem>
#include "keymanager.h"

class SpaceShip : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit SpaceShip(QObject *parent = nullptr, QString imagePath = nullptr);
    int removalCheck();
    void createBullet(int side = 1);

    int side;

public slots:
    virtual void onTimer() = 0;
    void toggleCheckText(bool show);

signals:

protected:
    void setUpDelay(int delay);
    void setUpCheckText();
    void setCheckText(QString string);

    virtual void groupCheckTextInfo() = 0;

    int width = 100;
    int height = 100;
    float xSpeed;
    float ySpeed;
    int bulletSpeed;
    int shootDelay;
    const int baseShootDelay = 5000;
    bool shootAvl = true;
    QGraphicsTextItem *checkText;

private:
    QTimer* timerBullet = nullptr;

private slots:
    void shootIsAvl();
};

#endif // SPACESHIP_H
