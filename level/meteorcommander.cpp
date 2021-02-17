#include "meteorcommander.h"
#include "graphic-objects/meteor.h"
MeteorCommander::MeteorCommander(QGraphicsScene *scene, QObject *parent) : QObject(parent)
{
    this->scene = scene;
}

void MeteorCommander::startSpawningMeteors()
{
    createMeteor();
    connect(timer, &QTimer::timeout, this, &MeteorCommander::onSpawnTimer);
    timer->start(spawnRate);
}

void MeteorCommander::onSpawnTimer()
{
    createMeteor();
}

void MeteorCommander::createMeteor()
{
    Meteor* meteor = new Meteor();

    meteor->addToScene(scene);
    meteorCount++;
}
