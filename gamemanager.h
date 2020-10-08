#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "ScoreBar.h"
#include "hero.h"
#include "graphicsview.h"

#include <QObject>

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);


private:
    void createFullScreenImage(QString imagePath);
    void createBackground();
    QString gameOverImagePath = ":/images/gameOver.png";
    ScoreBar* scoreBar;
    QGraphicsScene* scene;
    GraphicsView* view;
    Hero* hero;
    QString backgroundImagePath = ":/images/background.png";

    int sceneWidth = 600;
    int sceneHeight = 1000;



private slots:
    void gameOver();
    void createEndScreen();
    void changeScore(int score);
    void createWinScreen();

};

#endif // GAMEMANAGER_H
