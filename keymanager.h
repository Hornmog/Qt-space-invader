#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QWidget>
#include <QKeyEvent>
#include <QSet>


class KeyManager : public QWidget
{
    Q_OBJECT
public:
    explicit KeyManager(QWidget* widget = nullptr);
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

signals:
    void heroKeyPressed(int key);
    void logKeyPressed();
    void heroKeyReleased(int key);
    void keyRPressed();
    void keyPPressed();

};

#endif // KEYMANAGER_H
