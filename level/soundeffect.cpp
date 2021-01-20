#include "soundeffect.h"
#include <QDebug>
#include <QEventLoop>
#include <QSoundEffect>
SoundEffect::SoundEffect(QString path, qreal volume)
// I'd make "volume" a named argument
{
    // So you create a sound effect, play it, then don't delete it...
    // and just create a new object every time you need to do a sound effect.
    // I feel like it's a recipe for a memory leak.
    // Possible a static function would work better here?
    // Alternatively, there _is_ a sound effect object, but they play() function
    // is called from the same object each time; either by storing a pointer
    // to the relevant object or via singletone (though the latter might be a bit of an overkill here).s
    QSoundEffect *effect = new QSoundEffect();
    effect->setSource(QUrl("qrc" + path));
    effect->setLoopCount(1);
    effect->setVolume(volume);
    effect->play();
    qDebug() << "testing";
}
