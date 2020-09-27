#include "ScoreBar.h"

ScoreBar::ScoreBar()
{
    toPlainText();
    this->setPlainText(QString::number(0));
}

void ScoreBar::setScore(int new_score)
{
    this->setPlainText(QString::number(new_score));
}
