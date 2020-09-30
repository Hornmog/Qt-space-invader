#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "ScoreBar.h"
#include "hero.h"

#include <QObject>

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);


private:
    ScoreBar* scoreBar;
    QGraphicsScene* scene;
    Hero* hero;

private slots:
    void gameOver();
    void changeScore(int score);
};

#endif // GAMEMANAGER_H
