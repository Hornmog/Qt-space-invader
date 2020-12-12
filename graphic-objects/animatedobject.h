#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMovie>

class AnimatedObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    AnimatedObject(QObject *parent = nullptr, QString imagePath = nullptr);
    void setSize(int width, int height);
    int getWidth() const;
    int getHeight() const;

private slots:
    void nextFrame();
private:
    QString imagePath;
    QMovie* gif;
    int frameCounter = 0;

protected:
    int width = 100, height = 100;
};

#endif // GRAPHICSOBJECT_H
