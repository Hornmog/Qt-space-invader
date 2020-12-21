#include "audiomanager.h"
#include "consts.h"
#include <QtMultimedia/QSound>

AudioManager::AudioManager(QObject *parent) : QObject(parent)
{
    background = new QSound(AudioPaths::background);
    background->setLoops(QSound::Infinite);
}

void AudioManager::playBackground()
{
    background->play();
}

void AudioManager::stopBackground()
{
    background->stop();
}

void AudioManager::playEnemyDestroyed()
{

}
