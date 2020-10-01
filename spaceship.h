#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsRectItem>

class SpaceShip : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit SpaceShip(QObject *parent = nullptr);
    bool removalCheck();
    void createBullet();

public slots:
    virtual void onTimer() = 0;

signals:

protected:
    void setUpDelay(int delay);

    int width;
    int height;
    int speed;
    int bulletSpeed;
    int shootDelay;
    bool shootAvl = true;

private:
    QTimer* timerBullet = nullptr;
private slots:
    void shootIsAvl();

};

#endif // SPACESHIP_H
