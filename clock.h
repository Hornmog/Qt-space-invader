#ifndef CLOCK_H
#define CLOCK_H
#include <QElapsedTimer>
#include <QObject>

class Clock : public QObject, public QElapsedTimer
{
    Q_OBJECT
public:
    static Clock* getClock();
    void pause();
    void resume();
    int getTime();
    static bool isPaused();
    void start();

signals:
    void pauseSignal();
    void resumeSignal();

private:
    Clock();
    static Clock* clockPointer;
    static bool paused;
    int timeBeforePause;

};

#endif // CLOCK_H
