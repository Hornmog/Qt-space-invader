#include "graphicsview.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>


GraphicsView::GraphicsView(QGraphicsScene * scene) : QGraphicsView(scene) {
    //TODO: scroll bar policy ?
    QRect rect = QApplication::desktop()->screenGeometry(this);       // get size of a user's screen to position game window
    this->setGeometry(rect.width()/2 - scene->width()/2, rect.height()/2 - scene->height()/2, scene->width(), scene->height());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->show();

    this->setFixedSize(scene->width(), scene->height());
    //resize window ?
}
