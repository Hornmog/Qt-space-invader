#include "graphicsview.h"


GraphicsView::GraphicsView(QGraphicsScene * scene) : QGraphicsView(scene) {
    //TODO: scroll bar policy ?
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->show();
    this->setFixedSize(800,600);
    //resize window ?
}
