#include "clock.h"
#include <QTime>

Clock* Clock::clockPointer = nullptr;

Clock::Clock() : QElapsedTimer()
{

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


}

void Clock::resume()
{
    paused = false;
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
