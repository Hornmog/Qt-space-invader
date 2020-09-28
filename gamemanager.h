#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "ScoreBar.h"

#include <QObject>

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);

public slots:
    void changeScore(int score);

private:
    ScoreBar *scoreBar;
};

#endif // GAMEMANAGER_H
