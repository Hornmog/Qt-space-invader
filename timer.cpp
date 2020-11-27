#include "timer.h"
#include <QDebug>

Timer::Timer() : QTimer()
{
    QTimer* us = this;
    connect(us, SIGNAL(timeout()), this, SLOT(timeoutCheckInterval()));
}

void Timer::pause()
{

    timeInterval = this->interval();
    timeLeft = this->remainingTime();
    this->stop();
    paused = true;
}

void Timer::resume()
{
    this->start(timeLeft);
    resumed = true;
    paused = false;
}

bool Timer::isPaused()
{
    return paused;
}

void Timer::timeoutCheckInterval() {
    if (resumed) {
        this->stop();
        this->start(timeInterval);
        resumed = false;
    }
}
