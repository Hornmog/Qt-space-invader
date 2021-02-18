#include "meteorcommander.h"
#include "graphic-objects/meteor.h"
#include "utils/coordpair.h"
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QLabel>
#include "utils/timer.h"

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
    createWarningSign(meteor->getCurrPos());
    auto addMeteor = [this, meteor]() {meteor->addToScene(scene);};
    QTimer::singleShot(warningDelay, addMeteor);
    meteorCount++;
}

void MeteorCommander::createWarningSign(CoordPair coord)
{
    QLabel *warning = new QLabel();
    QPixmap image(ImagePaths::pause);
    warning->setPixmap(image.scaled(10, 75));
    warning->setAttribute(Qt::WA_TranslucentBackground);
    //warning->setZValue(ScenePriority::pause);

    int offset = 5;
    if(coord.x < 0){
        warning->move(offset, coord.y);
    }else{
        warning->move(sceneWidth - 10 - offset, coord.y);
    }
    scene->addWidget(warning);
    warning->show();
    QPropertyAnimation *blink = new QPropertyAnimation(warning, "windowOpacity");
    blink->setDuration(warningDelay/warningLoopCount);
    blink->setStartValue(0.0);
    blink->setKeyValueAt(0.5,1.0);
    blink->setEndValue(0.0);
    blink->setEasingCurve(QEasingCurve::InQuad);
    blink->setLoopCount(warningLoopCount);
    blink->start(QPropertyAnimation::DeleteWhenStopped);
}
