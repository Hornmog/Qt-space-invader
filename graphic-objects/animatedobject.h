#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMovie>
#include "movingobject.h"

class AnimatedObject : virtual public QObject, virtual public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    AnimatedObject(QObject *parent = nullptr, QString imagePath = nullptr, int width = 100, int height = 100);
    void setSize(int width, int height);
    void setTemporaryAnimation(QString path);
    int getWidth() const;
    int getHeight() const;

private slots:
    void nextFrame(int frameNumber);
private:
    QString imagePath;
    QMovie* gif;
    bool isDefaultGif = true;
    // If that is is used for replacing the current QMovie with another one, the name is confusing.

protected:
    int width = 100, height = 100;
};

#endif // GRAPHICSOBJECT_H
