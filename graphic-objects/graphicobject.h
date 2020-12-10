#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>

class GraphicObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GraphicObject(QObject *parent = nullptr, QString imagePath = nullptr, int objectType = 0);
private slots:
    void nextFrame();
private:
    QString imagePath;
    int frameCounter = 0;
    int width, height;
    int scenePriority;
};

#endif // GRAPHICSOBJECT_H
