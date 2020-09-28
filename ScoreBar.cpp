#include "ScoreBar.h"
#include <QFont>

ScoreBar::ScoreBar()
{
    QFont font = QFont("Times", 18);
    this->setFont(font);
    this->setPlainText(QString::number(0));
}

void ScoreBar::setScore(int new_score)
{
    this->setPlainText(QString::number(new_score));
}
