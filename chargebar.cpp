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
    linearGrad.setColorAt(0, QColor(90, 3, 252));
    linearGrad.setColorAt(1, QColor(3, 194, 252));

    QBrush brush(linearGrad);

    this->setBrush(brush);

}

void ChargeBar::setCharge(float charge)
{
    this->setRect(innitX, innitY, maxWidth * (charge / 100), height);
}
