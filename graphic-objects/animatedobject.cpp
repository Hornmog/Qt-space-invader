#include "animatedobject.h"
#include "timer.h"
#include "consts.h"
#include <QDebug>

AnimatedObject::AnimatedObject(QObject *parent, QString imagePath) : QObject(parent)
{
    this->imagePath = imagePath;
    gif = new QMovie(imagePath);
    gif->start();
    nextFrame();


    connect(gif, &QMovie::updated, this, &AnimatedObject::nextFrame);
}

void AnimatedObject::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void AnimatedObject::nextFrame()
{
    /// TODO: make width and height different for different objects
    this->setPixmap(gif->currentPixmap().scaled(width, height));
}

int AnimatedObject::getHeight() const
{
    return height;
}

int AnimatedObject::getWidth() const
{
    return width;
}
