#include "graphicsview.h"


GraphicsView::GraphicsView(QGraphicsScene * scene) : QGraphicsView(scene) {
    //TODO: scroll bar policy ?
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->show();
    this->setFixedSize(scene->width(), scene->height());
    //resize window ?
}
