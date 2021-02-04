#include "chargebar.h"
#include <QGraphicsScene>
#include "consts.h"
ChargeBar::ChargeBar(QObject *parent, QGraphicsScene* scene)
{
    this->setRect(maxWidth/2, height, maxWidth, height);
    this->setZValue(ScenePriority::heroAttributes);
    scene->addItem(this);

//    QGradient* gradient = new QGradient();
//    gradient->setColorAt(0, QColor::fromRgbF(0, 0, 1, 1));
//    gradient->setColorAt(1, QColor::fromRgbF(1, 0, 0, 1));
//    gradient->setSpread(QGradient::PadSpread);

//    QLinearGradient linearGrad(QPointF(100, 100), QPointF(200, 200));
//    linearGrad.setColorAt(0, Qt::black);
//    linearGrad.setColorAt(1, Qt::white);

//    QBrush brush(*gradient);

//    this->setBrush(brush);
    this->setPen(QPen(Qt::red));

}

void ChargeBar::setCharge(float charge)
{
//    QRectF curRect = this->boundingRect();
//    curRect.setWidth();

    this->setRect(innitX, innitY, maxWidth * (charge / 100), height);
}
