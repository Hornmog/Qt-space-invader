#ifndef CHARGEBAR_H
#define CHARGEBAR_H

#include <QObject>
#include <QGraphicsRectItem>

class ChargeBar : public QGraphicsRectItem
{

public:
    ChargeBar(QObject *parent = nullptr, QGraphicsScene* scene = nullptr);
    void setCharge(float charge);
private:
    int maxWidth = 100;
    int height = 20;
    int innitX = maxWidth/2;
    int innitY = height;
};

#endif // CHARGEBAR_H
