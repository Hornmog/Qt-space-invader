#include "leaderboardwindow.h"

#include <QJsonObject>
#include <QJsonArray>
#include "consts.h"
#include <QDebug>

LeaderBoardWindow::LeaderBoardWindow() : QMessageBox()
{

}

void LeaderBoardWindow::setLeaderboard(QJsonObject leaderboard)
{
    QString leaderBoardInfo = "";

    for(int i = 0; i < 3; i++){
        QJsonObject player = leaderboard.value(JsonNames::players).toArray()[i].toObject();
        qDebug() << player;

        leaderBoardInfo += player.value(JsonNames::name).toString() + " - " +
                QString::number(player.value(JsonNames::enemiesKilled).toInt()) + "\n";

    }
    qDebug() << leaderBoardInfo;
    this->setText("<i>LeaderBoard</i>");
    this->setInformativeText(leaderBoardInfo);
}
