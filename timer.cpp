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
}

void Timer::resume()
{
    this->start(timeLeft);
    resumed = true;
}

void Timer::timeoutCheckInterval() {
    if (resumed) {
        this->stop();
        this->start(timeInterval);
        resumed = false;
    }
}
