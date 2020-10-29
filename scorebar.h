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
    void setScore(int new_score);
    int type() const override {return TypeIndex::scoreBar;}

private:
};

#endif // SCORE_H
