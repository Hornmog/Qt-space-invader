#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QGraphicsObject>

class Hero: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Hero();
    void keyPressEvent(QKeyEvent * event);
    int height = 100;
    int width = 100;
    bool shootAvl = 1;

public slots:
    void shootIsAvl();
};

#endif // MYRECT_H
