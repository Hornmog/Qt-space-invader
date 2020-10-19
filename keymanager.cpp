#include "keymanager.h"
#include <QKeyEvent>
#include "graphic-objects/hero.h"

KeyManager::KeyManager(QWidget *widget)
{
    this->setFocus();
    logShow = true;
}

void KeyManager::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if (heroCommands.contains(key))
    {
        heroKeyPressed(key);
    }

    if (key == Qt::Key_L){
        logKeyPressed(logShow);
        logShow = !logShow;
    }
}

void KeyManager::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key == Qt::Key_Left || key == Qt::Key_Right){
        heroKeyReleased(key);
    }
}
