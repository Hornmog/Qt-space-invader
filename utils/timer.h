#ifndef TIMER_H
#define TIMER_H
#include <QTimer>
#include "utils/clock.h"
#include <functional>

class Timer : public QTimer
{
    Q_OBJECT
public:
    using extfunc_t = std::function<void()>;
    Timer();
    void connectExternalMethod(extfunc_t);

public slots:
    void start(int msec);

private:
    void callExternalMethod();
    extfunc_t method;
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
