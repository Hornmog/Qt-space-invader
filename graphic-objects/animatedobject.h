#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMovie>

class AnimatedObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    AnimatedObject(QObject *parent = nullptr, QString imagePath = nullptr, int width = 0, int height = 0);
private slots:
    void nextFrame();
private:
    QString imagePath;
    QMovie* gif;
    int frameCounter = 0;
    int width, height;
};

#endif // GRAPHICSOBJECT_H
