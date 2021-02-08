#include "chargebar.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QLinearGradient>
#include "consts.h"

ChargeBar::ChargeBar(QObject *parent, QGraphicsScene* scene)
{
    this->setRect(maxWidth/2, height, maxWidth, height);
    this->setZValue(ScenePriority::heroAttributes);
    scene->addItem(this);

    QLinearGradient linearGrad(this->boundingRect().topLeft(), this->boundingRect().bottomRight());
    linearGrad.setColorAt(0, Qt::red);
    linearGrad.setColorAt(1, Qt::blue);

    QBrush brush(linearGrad);

    this->setBrush(brush);
    this->setPen(QPen(Qt::red));

}

void ChargeBar::setCharge(float charge)
{
    this->setRect(innitX, innitY, maxWidth * (charge / 100), height);
}
