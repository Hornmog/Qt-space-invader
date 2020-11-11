#include "scorebar.h"
#include <QFont>
#include "consts.h"
#include <QGraphicsScene>

ScoreBar::ScoreBar()
{
    QFont font = QFont("Times", 18);
    QColor color = QColor("white");
    this->setFont(font);
    this->setDefaultTextColor(color);
    this->setPlainText(QString::number(0));
    this->setZValue(ScenePriority::text);
}

void ScoreBar::setScore(int newScore)
{
    score = newScore;
    this->setPlainText(QString::number(newScore));
}
