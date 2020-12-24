#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView();
    void setScene(QGraphicsScene* scene);
private:
};

#endif // GRAPHICSVIEW_H
