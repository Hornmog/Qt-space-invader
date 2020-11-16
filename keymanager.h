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
    void logKeyPressed(bool logShow);
    void heroKeyReleased(int key);
    void keyRPressed();

private:
    bool logShow;
    QSet<int> arrowKeys = {Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down};
    QSet<int> heroCommands = {Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down, Qt::Key_Space};

};

#endif // KEYMANAGER_H
