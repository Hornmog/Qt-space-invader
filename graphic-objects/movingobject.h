#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <QObject>
#include <QGraphicsScene>
#include "utils/coordpair.h"
#include "checktext.h"
#include "utils/timer.h"

class MovingObject : virtual public QObject, virtual public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit MovingObject(QObject *parent = nullptr);
    ~MovingObject() override;
    static bool checkTextVisible;
    virtual void addToScene(QGraphicsScene* scene);

private:
    bool checkTextOnScene = false;

protected:
    QGraphicsItem* collisionCheck(int typeIndex);
    int bulletCollisionCheck();
    void setUpCheckText();
    virtual void groupCheckTextInfo() = 0;
    CoordPair speed = CoordPair(0,0);
    CheckText *checkText;
    Timer* mainTimer;
    Side side;

public slots:
    virtual void onTimer() = 0;
    void toggleCheckText();

signals:

};

#endif // MOVINGOBJECT_H
