#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMovie>
#include "movingobject.h"

class Animator : public QObject
{
    Q_OBJECT
public:
    Animator(QObject *parent = nullptr, QGraphicsPixmapItem *item = nullptr,
             QString imagePath = nullptr, int width = 0, int height = 0);
    //void setSize(int width, int height);
    void setTemporaryAnimation(QString path);

private slots:
    void nextFrame(int frameNumber);

private:
    QGraphicsPixmapItem * item;
    QString imagePath;
    QMovie* gif;
    bool isDefaultGif = true;
    int width, height;
    // If that is is used for replacing the current QMovie with another one, the name is confusing.
};

#endif // GRAPHICSOBJECT_H
