#include "animatedobject.h"
#include "utils/timer.h"
#include "consts.h"
#include <QDebug>

AnimatedObject::AnimatedObject(QObject *parent, QString imagePath, int width, int height)
{
    this->imagePath = imagePath;
    this->width = width;
    this->height = height;
    gif = new QMovie(imagePath);
    gif->start();
    nextFrame(0);

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
    qDebug() << "Current nonDefault gif frame: " << gif->currentFrameNumber();
    qDebug() << "Current nonDefault gif frameCount: " << gif->frameCount();
}

void AnimatedObject::nextFrame(int frameNumber)
{

    if(!isDefaultGif && frameNumber + 1 >= gif->frameCount()){
        gif = new QMovie(imagePath);
        gif->start();
        isDefaultGif = true;
        qDebug() << "Changing back to default: curr gif frame: " << gif->currentFrameNumber()
                 << "gifCount: " << gif->frameCount();
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
