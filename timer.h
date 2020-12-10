#ifndef TIMER_H
#define TIMER_H
#include <QTimer>
#include "clock.h"

class Timer : public QTimer
{
    Q_OBJECT
public:
    Timer();

public Q_SLOTS:
    void start(int msec);

private:
    bool intervalSet = false;
    bool wasResumedOnThisIteration = false;
    bool paused = true;
    int timeLeft;
    int timeInterval;
private slots:
    void timeoutCheckInterval();
    void pause();
    void resume();
};

#endif // TIMER_H
