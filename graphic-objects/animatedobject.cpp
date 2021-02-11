#include "animatedobject.h"
#include "utils/timer.h"
#include "consts.h"
#include <QDebug>

Animator::Animator(QObject *parent, QGraphicsPixmapItem *item, QString imagePath,
                   int width, int height) : QObject(parent)
{
    this->width = width;
    this->height = height;
    this->imagePath = imagePath;
    this->item = item;
    gif = new QMovie(imagePath);
    gif->start();
    nextFrame(0);

    connect(gif, &QMovie::frameChanged, this, &Animator::nextFrame);
}

void Animator::setTemporaryAnimation(QString path)
{
    gif = new QMovie(path);
    gif->start();
    isDefaultGif = false;
    qDebug() << "Current nonDefault gif frame: " << gif->currentFrameNumber();
    qDebug() << "Current nonDefault gif frameCount: " << gif->frameCount();
}

void Animator::nextFrame(int frameNumber)
{    
    if(!isDefaultGif && frameNumber + 1 >= gif->frameCount()){
        gif = new QMovie(imagePath);
        gif->start();
        isDefaultGif = true; 
        qDebug() << "Changing back to default: curr gif frame: " << gif->currentFrameNumber()
                 << "gifCount: " << gif->frameCount();
    }
    item->setPixmap(gif->currentPixmap().scaled(width, height));
}
