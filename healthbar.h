#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>

class HealthBar : public QObject
{
    Q_OBJECT
public:
    explicit HealthBar(QObject *parent = nullptr, QGraphicsScene* scene = nullptr);
    void setLives(int value);

private:
    void removeLives(int value);
    void addLives(int value);
    QGraphicsPixmapItem* createHeart(int i);

    QList<QGraphicsPixmapItem*> lifeList;
    QGraphicsScene* scene;
    int lives = 0;
    int heartWidth = 50;
    int heartHeight = 50;
    int heartOffset = 20;

signals:

};

#endif // HEALTHBAR_H
