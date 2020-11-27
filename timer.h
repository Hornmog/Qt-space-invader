#ifndef TIMER_H
#define TIMER_H
#include <QTimer>

class Timer : public QTimer
{
    Q_OBJECT
public:
    Timer();
    void pause();
    void resume();
    bool isPaused();
private:
    bool resumed = false;
    bool paused = false;
    int timeLeft;
    int timeInterval;
private slots:
    void timeoutCheckInterval();
};

#endif // TIMER_H
