#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QSound>

class AudioManager : public QObject
{
    Q_OBJECT
public:
    explicit AudioManager(QObject *parent = nullptr);
    void playBackground();
    void stopBackground();
    void playEnemyDestroyed();
signals:

private:
    QSound* background;
};

#endif // AUDIOMANAGER_H
