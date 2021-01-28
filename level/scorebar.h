#ifndef SCOREBAR_H
#define SCOREBAR_H

#include <QObject>
#include <QGraphicsTextItem>
#include "consts.h"

class ScoreBar :public QGraphicsTextItem
{
    Q_OBJECT
public:
    ScoreBar();
    void setScore(int newScore);
    int type() const override {return TypeIndex::scoreBar;}

    int score = 0;

private:
};

#endif // SCORE_H
