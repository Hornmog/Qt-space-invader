#include "keymanager.h"
#include <QKeyEvent>
#include "hero.h"

KeyManager::KeyManager(QWidget *widget)
{
    this->setFocus();
    logShow = true;
}

void KeyManager::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if (key == Qt::Key_Left || key == Qt::Key_Right ||
        key == Qt::Key_Up || key == Qt::Key_Down || key == Qt::Key_Space)
    {
        heroKeyPressed(key);
    }

    if (key == Qt::Key_L){
        logKeyPressed(logShow);
        logShow = !logShow;
    }
}
