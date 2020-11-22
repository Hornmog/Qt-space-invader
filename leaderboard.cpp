#include "leaderboard.h"
#include "consts.h"

LeaderBoard::LeaderBoard()
{
    this->setFileName(leaderBoardFileName);

}

QJsonObject LeaderBoard::load()
{
    QJsonObject json;
    if (!QFile::exists(leaderBoardFileName)){
        json = createNew();
    } else {
        this->open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray saveData = this->readAll();
        json = QJsonDocument::fromJson(saveData).object();
    }

    this->close();
    qDebug() << json;
    return json;
}

void LeaderBoard::save(QJsonObject obj)
{
    this->open(QIODevice::WriteOnly | QIODevice::Text);
    this->write(QJsonDocument(obj).toJson());
    this->close();
}

void LeaderBoard::update(QString name, int enemiesKilled)
{
    if(name == ""){
        return;
    }
    QJsonObject json = load();
    for(int i = 0; i < numOfPlayers; i++){
        QJsonObject playerTemp = json.value(JsonNames::players)[i].toObject();
        qDebug() << "Our tested player: " << playerTemp;
        qDebug() << "kills: " << playerTemp.value(JsonNames::enemiesKilled).toInt();

        if (enemiesKilled > playerTemp.value(JsonNames::enemiesKilled).toInt()) {
            QJsonArray tempArr = json[JsonNames::players].toArray();
            tempArr.insert(i, createPlayer(name, enemiesKilled));
            tempArr.pop_back();

            json[JsonNames::players] = tempArr;
            save(json);
            break;
        }
    }

}

QJsonObject LeaderBoard::createNew()
{
    QJsonArray players;

    for(int i = 0; i < numOfPlayers; i++){
        players.push_back(createPlayer());
    }

    QJsonObject json;
    json.insert(JsonNames::players, players);
    return json;
}

QJsonObject LeaderBoard::createPlayer(QString name, int enemiesKilled)
{
    QJsonObject player;
    player[JsonNames::name] = name;
    player[JsonNames::enemiesKilled] = enemiesKilled;
    return player;
}
