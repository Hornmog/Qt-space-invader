#ifndef TIMER_H
#define TIMER_H
#include <QTimer>
#include "clock.h"

class Timer : public QTimer
{
    Q_OBJECT
public:
    Timer();

private:
    bool resumed = false;
    bool paused = false;
    int timeLeft;
    int timeInterval;
private slots:
    void timeoutCheckInterval();
    void pause();
    void resume();
};

#endif // TIMER_H
