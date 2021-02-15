#include "meteorcommander.h"
#include "graphic-objects/meteor.h"
MeteorCommander::MeteorCommander(QObject *parent) : QObject(parent)
{

}

void MeteorCommander::startSpawningMeteor()
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
    totalSpawned++;
}
