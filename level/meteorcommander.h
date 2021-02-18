#ifndef METEORCOMMANDER_H
#define METEORCOMMANDER_H

#include <QObject>
#include "utils/timer.h"
#include "utils/coordpair.h"
#include "QGraphicsScene"

class MeteorCommander : public QObject
{
    Q_OBJECT
public:
    explicit MeteorCommander(QGraphicsScene* scene, QObject *parent = nullptr);
    void startSpawningMeteors();

signals:
    void logKeyPressed();

public slots:
    void onSpawnTimer();

private:
    void createMeteor();
    void createWarningSign(CoordPair coord);
    Timer* timer = new Timer();
    int spawnRate = 5000;
    int meteorCount = 0;
    int warningDelay = 1500;
    int warningLoopCount = 3;

    QGraphicsScene *scene;

};


#endif // METEORCOMMANDER_H
