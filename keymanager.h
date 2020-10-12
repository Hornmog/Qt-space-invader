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
    explicit KeyManager(QObject *parent = nullptr);
    void keyPressEvent(QKeyEvent * event) override;

signals:

};

#endif // KEYMANAGER_H
