#include "graphicsview.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

#include "consts.h"

GraphicsView::GraphicsView() : QGraphicsView() {
    //TODO: scroll bar policy ?
    QRect rect = QApplication::desktop()->screenGeometry(this);       // get size of a user's screen to position game window
    this->setGeometry(rect.width()/2 - sceneWidth, rect.height()/2 - sceneHeight, sceneWidth, sceneHeight);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->show();

    this->setFixedSize(sceneWidth, sceneHeight);
    //resize window ?
}
