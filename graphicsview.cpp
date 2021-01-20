#include "graphicsview.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

#include "consts.h"

GraphicsView::GraphicsView() {
}

void GraphicsView::setScene(QGraphicsScene *scene)
{
    QGraphicsView::setScene(scene);
    QRect rect = QApplication::desktop()->screenGeometry(this);
    qDebug() << "user window size: " << rect.width() << " " << rect.height();
    qDebug() << "scene consts: " << sceneWidth << " " << sceneHeight;
    // get size of a user's screen to position game window
    this->setGeometry((rect.width() - sceneWidth) / 2, (rect.height() - sceneHeight) / 2, sceneWidth, sceneHeight);
    qDebug() << "current view pos: " << this->pos();
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->show();

    this->setFixedSize(sceneWidth, sceneHeight);
}
