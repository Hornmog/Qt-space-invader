#ifndef CLOCK_H
#define CLOCK_H
#include <QElapsedTimer>
#include <QObject>

class Clock : public QElapsedTimer
{
    Q_OBJECT
public:
    static Clock* getClock();

    void pause();
    void resume();
    int getTime();
signals:
    void pauseSignal();
    void resumeSignal();

private:
    Clock();
    static Clock* clockPointer;
    bool paused = false;
    int timeBeforePause;

};

#endif // CLOCK_H
