#include "animatedobject.h"
#include "timer.h"
#include "consts.h"
#include <QDebug>

AnimatedObject::AnimatedObject(QObject *parent, QString imagePath, int width, int height) : QObject(parent)
{
    this->imagePath = imagePath;
    this->width = width;
    this->height = height;
    gif = new QMovie(ImagePaths::hero);
    gif->start();
    nextFrame();


    connect(gif, &QMovie::updated, this, &AnimatedObject::nextFrame);
}

void AnimatedObject::nextFrame()
{
    /// TODO: make width and height different for different objects
    this->setPixmap(gif->currentPixmap().scaled(width, height));
}
