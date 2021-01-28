#include "clock.h"
#include <QTime>

Clock* Clock::clockPointer = nullptr;
bool Clock::paused = false;

Clock::Clock() {

}

bool Clock::isPaused()
{
    return paused;
}

void Clock::start()
{
    QElapsedTimer::start();
    paused = false;
}

Clock* Clock::getClock()
{
    if(clockPointer == nullptr){
        clockPointer = new Clock();
    }
    return clockPointer;
}

void Clock::pause()
{
    timeBeforePause = this->elapsed();
    paused = true;
    emit pauseSignal();
}

void Clock::resume()
{
    paused = false;
    emit resumeSignal();
}

int Clock::getTime()
{
    if(paused){
        return timeBeforePause;
    }
    else{
        return this->elapsed();
    }
}
