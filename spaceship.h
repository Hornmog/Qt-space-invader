#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsRectItem>


class SpaceShip : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit SpaceShip(QObject *parent = nullptr, QString imagePath = nullptr);
    bool removalCheck();
    void createBullet(int bulletType = 1);

public slots:
    virtual void onTimer() = 0;

signals:

protected:
    void setUpDelay(int delay);


    int width = 100;
    int height = 100;
    int xSpeed;
    int ySpeed;
    int bulletSpeed;
    int shootDelay;
    const int baseShootDelay = 5000;
    bool shootAvl = true;

private:
    QTimer* timerBullet = nullptr;
private slots:
    void shootIsAvl();

};

#endif // SPACESHIP_H
