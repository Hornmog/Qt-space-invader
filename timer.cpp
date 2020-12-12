#include "timer.h"
#include <QDebug>
#include <stdexcept>

Timer::Timer() : QTimer()
{
    QTimer* us = this;
    connect(us, &QTimer::timeout, this, &Timer::timeoutCheckInterval);
    connect(Clock::getClock(), &Clock::pauseSignal, this, &Timer::pause);
    connect(Clock::getClock(), &Clock::resumeSignal, this, &Timer::resume);
}

void Timer::start(int msec)
{
    QTimer::start(msec);
    paused = false;
    intervalSet = true;
}

void Timer::pause()
{
    if(!paused){
        timeInterval = this->interval();
        timeLeft = this->remainingTime();
        if (timeLeft == -1) {
             throw std::domain_error("Time interval = -1, timer isn't active");
        }
        this->stop();
        paused = true;
    }
}

void Timer::resume()
{
    if(paused && intervalSet){
        //qDebug() << "Time left: " << timeLeft;
        this->start(timeLeft);
        wasResumedOnThisIteration = true;
        paused = false;
    }
}

void Timer::timeoutCheckInterval() {
    if(!isSingleShot() && wasResumedOnThisIteration) {
        this->stop();
        this->start(timeInterval);
        wasResumedOnThisIteration = false;
    } else if (isSingleShot()) {
        paused = true;
    }
}
