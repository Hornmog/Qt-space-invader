#ifndef SCOREBAR_H
#define SCOREBAR_H

#include <QObject>
#include <QGraphicsTextItem>

class ScoreBar :public QGraphicsTextItem
{
    Q_OBJECT
public:
    ScoreBar();
    void setScore(int new_score);

private:
};

#endif // SCORE_H
