#include "keymanager.h"
#include <QKeyEvent>
#include "graphic-objects/hero.h"
#include "consts.h"

KeyManager::KeyManager(QWidget *widget) : QWidget(widget)
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

    else if (key == Qt::Key_L){
        logKeyPressed(logShow);
        logShow = !logShow;
    }
    else if (key == Qt::Key_R){
        keyRPressed();
    }
    else if (key == Qt::Key_P){
        keyPPressed();
    }
}

void KeyManager::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if(arrowKeys.contains(key)){
        heroKeyReleased(key);
    }
}
