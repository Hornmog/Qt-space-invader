#include "keymanager.h"
#include <QKeyEvent>
#include "graphic-objects/hero.h"
#include "consts.h"

KeyManager::KeyManager(QWidget *widget) : QWidget(widget)
{
    this->setFocus();

}

void KeyManager::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    if (heroCommands.contains(key))
    {
        emit heroKeyPressed(key);
    }

    else if (key == Qt::Key_L){
        MovingObject::checkTextVisible = !MovingObject::checkTextVisible;
        qDebug() << "KeyManager set checkText to " << MovingObject::checkTextVisible;
        emit logKeyPressed();
    }
    else if (key == Qt::Key_R){
        emit keyRPressed();
    }
    else if (key == Qt::Key_P){
        emit keyPPressed();
    }
}

void KeyManager::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if(arrowKeys.contains(key)){
        emit heroKeyReleased(key);
    }
}
