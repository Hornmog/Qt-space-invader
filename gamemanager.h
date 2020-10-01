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
<<<<<<< HEAD
    QString gameOverImagePath = ":/images/gameOver.png";
=======
    QString imagePath = "D://Qt/Projects/Test_game1/gameOver.png";
>>>>>>> spaceship
    ScoreBar* scoreBar;
    QGraphicsScene* scene;
    Hero* hero;

private slots:
    void gameOver();
    void createEndScreen();
    void changeScore(int score);
};

#endif // GAMEMANAGER_H
