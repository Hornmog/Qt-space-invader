#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QWidget>
#include <QKeyEvent>


class KeyManager : public QWidget
{
    Q_OBJECT
public:
    explicit KeyManager(QWidget* widget = nullptr);
    void keyPressEvent(QKeyEvent* event) override;


signals:
    void heroKeyPressed(int key);

};

#endif // KEYMANAGER_H
