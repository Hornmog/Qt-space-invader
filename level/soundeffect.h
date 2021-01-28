#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <QMediaPlayer>
#include <QSoundEffect>
class SoundEffect
{
public:
    SoundEffect();
    void play(QString path, qreal volume, int loopCount = 1);
private:
    QSoundEffect *effect;
};

#endif // SOUNDEFFECT_H
