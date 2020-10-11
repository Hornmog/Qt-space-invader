#include "ScoreBar.h"
#include <QFont>
#include "Const.h"
#include <QGraphicsScene>

ScoreBar::ScoreBar()
{
    QFont font = QFont("Times", 18);
    QColor color = QColor("white");
    this->setFont(font);
    this->setDefaultTextColor(color);
    this->setPlainText(QString::number(0));
    this->setZValue(ScenePriority::scoreBar);
}

void ScoreBar::setScore(int new_score)
{
    this->setPlainText(QString::number(new_score));
}
