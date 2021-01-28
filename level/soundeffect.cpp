#include "soundeffect.h"
#include <QDebug>
#include <QEventLoop>
#include <QSoundEffect>
SoundEffect::SoundEffect()
// I'd make "volume" a named argument
{
    effect = new QSoundEffect();
}

void SoundEffect::play(QString path, qreal volume, int loopCount)
{
    effect->setSource(QUrl("qrc" + path));
    effect->setLoopCount(loopCount);
    effect->setVolume(volume);
     effect->play();
}
