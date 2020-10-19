#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "scorebar.h"
#include "graphic-objects/hero.h"
#include "graphicsview.h"
#include "consts.h"

#include <QObject>

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);


private:
    void createFullScreenImage(QString imagePath);
    void createBackground();
    QString gameOverImagePath = ImagePaths::gameOverImagePath;
    ScoreBar* scoreBar;
    QGraphicsScene* scene;
    GraphicsView* view;
    Hero* hero;
    QString backgroundImagePath = ImagePaths::backgroundImagePath;

    int sceneWidth = 600;
    int sceneHeight = 1000;



private slots:
    void gameOver();
    void createEndScreen();
    void changeScore(int score);
    void createWinScreen();

};

#endif // GAMEMANAGER_H
