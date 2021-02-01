#include "animatedobject.h"
#include "utils/timer.h"
#include "consts.h"
#include <QDebug>

AnimatedObject::AnimatedObject(QObject *parent, QString imagePath, int width, int height) : QObject(parent)
{
    this->imagePath = imagePath;
    this->width = width;
    this->height = height;
    gif = new QMovie(imagePath);
    gif->start();
    nextFrame();

    connect(gif, &QMovie::frameChanged, this, &AnimatedObject::nextFrame);
}

void AnimatedObject::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void AnimatedObject::setTemporaryAnimation(QString path)
{
    gif = new QMovie(path);
    gif->start();
    isDefaultGif = false;
}

void AnimatedObject::nextFrame()
{
    if(!isDefaultGif && gif->currentFrameNumber() + 1 >= gif->frameCount()){
        gif = new QMovie(imagePath);
        gif->start();
        isDefaultGif = true;
    }

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
