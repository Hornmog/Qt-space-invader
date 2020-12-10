#include "graphicobject.h"
#include "timer.h"
#include "consts.h"

GraphicObject::GraphicObject(QObject *parent, QString imagePath, int objectType) : QObject(parent)
{
    this->imagePath = imagePath;

    switch (objectType){
        case 66666:
            width = objectSizes::bullet[0], height = objectSizes::bullet[1];
            scenePriority = ScenePriority::bullet;
            break;

        case 66667:
        case 66670:
            width = 100, height = 50;
            scenePriority = ScenePriority::spaceship;
            break;
    }

    this->setZValue(scenePriority);

    Timer* frameTimer = new Timer();
    connect(frameTimer, &QTimer::timeout, this, &GraphicObject::nextFrame);
    frameTimer->start(1000/numFrames);
}

void GraphicObject::nextFrame()
{
    QPixmap pixmap(imagePath + "default" + frameCounter + ".png");
    this->setPixmap(pixmap.scaled(width, height));
}
