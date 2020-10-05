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
    void createBackground();
    QString gameOverImagePath = ":/images/gameOver.png";
    ScoreBar* scoreBar;
    QGraphicsScene* scene;
    Hero* hero;
    QString backgroundImagePath = ":/images/background.png";

    int sceneWidth = 800;
    int sceneHeight = 800;



private slots:
    void gameOver();
    void createEndScreen();
    void changeScore(int score);

};

#endif // GAMEMANAGER_H