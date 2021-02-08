#include "meteor.h"
#include <QRandomGenerator>
#include "consts.h"
#include <QPixmap>
#include <QGraphicsScene>

Meteor::Meteor()
{
    CoordPair diff(0.2 * period_ms, 0.02 * period_ms);

    speed.x = QRandomGenerator::global()->bounded(diff.x * 2 + 1) - diff.x;
    speed.y = QRandomGenerator::global()->bounded(diff.y * 2 + 1) + diff.y;

    QPixmap meteorImage = QPixmap(ImagePaths::hero);
    size.x = QRandomGenerator::global()->bounded(50, 100);
    size.y = QRandomGenerator::global()->bounded(50, 100);
    this->setPixmap(meteorImage.scaled(size.x, size.y, Qt::KeepAspectRatio));

    this->setZValue(ScenePriority::meteor);
    this->setPos(-size.x, QRandomGenerator::global()->bounded(int(sceneHeight*0.25), int(sceneHeight - size.y)));

}

void Meteor::addToScene(QGraphicsScene *scene)
{
    scene->addItem(this);
    //scene->addItem(checkText);
}
