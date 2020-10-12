#include "keymanager.h"
#include <QKeyEvent>

KeyManager::KeyManager(QObject *parent) : QWidget(nullptr)
{

}

void KeyManager::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){

    }

}
