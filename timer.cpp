#include "timer.h"
#include <QDebug>

Timer::Timer() : QTimer()
{
    QTimer* us = this;
    connect(us, &QTimer::timeout, this, &Timer::timeoutCheckInterval);
    connect(Clock::getClock(), &Clock::pauseSignal, this, &Timer::pause);
    connect(Clock::getClock(), &Clock::resumeSignal, this, &Timer::resume);
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

void Timer::timeoutCheckInterval() {
    if (resumed) {
        this->stop();
        this->start(timeInterval);
        resumed = false;
    }
}
