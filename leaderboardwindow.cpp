#include "leaderboardwindow.h"

#include <QJsonObject>
#include <QJsonArray>
#include "consts.h"
#include <QDebug>

LeaderBoardWindow::LeaderBoardWindow() {

}

void LeaderBoardWindow::setLeaderboard(QJsonObject leaderboard)
{
    QString leaderBoardInfo = "";

    for(int i = 0; i < 3; i++){
        QJsonObject player = leaderboard.value(JsonNames::players).toArray()[i].toObject();

        leaderBoardInfo += player.value(JsonNames::name).toString() + " -\t" +
                QString::number(player.value(JsonNames::enemiesKilled).toInt()) + "\n";

    }
    this->setText("<p style=font-size:30px style=font-family:verdana> LeaderBoard: </p>");
    this->setInformativeText(leaderBoardInfo);
}
