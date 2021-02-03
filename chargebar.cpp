#include "chargebar.h"
#include <QGraphicsScene>
#include "consts.h"
ChargeBar::ChargeBar(QObject *parent, QGraphicsScene* scene)
{
    this->setRect(maxWidth/2, height, maxWidth, height);
    this->setZValue(ScenePriority::heroAttributes);
    scene->addItem(this);

//    QLinearGradient* gradient = new QLinearGradient();
//    gradient->setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
//    gradient->setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));

//    QBrush brush(*gradient);

    this->setBrush(Qt::blue);

}

void ChargeBar::setCharge(float charge)
{
//    QRectF curRect = this->boundingRect();
//    curRect.setWidth();

    this->setRect(innitX, innitY, maxWidth * (charge / 100), height);
}
