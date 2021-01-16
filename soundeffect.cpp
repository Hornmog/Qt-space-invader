#include "soundeffect.h"
#include <QDebug>
#include <QEventLoop>
#include <QSoundEffect>
SoundEffect::SoundEffect(QString path, qreal volume)
{
    QSoundEffect *effect = new QSoundEffect();
    effect->setSource(QUrl("qrc" + path));
    effect->setLoopCount(1);
    effect->setVolume(volume);
    effect->play();
    qDebug() << "testing";
}
