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
    QJsonObject json = load();
    bool inserted = false;
    int pos;

    for(int i = 0; i < numOfPlayers; i++){
        QJsonObject playerTemp = json.value(JsonNames::players).toArray()[i].toObject();

        if (enemiesKilled > QString::number(playerTemp.value(JsonNames::enemiesKilled).toInt())) {
                pos = i;
                inserted = true;
                break;
            }
    }

    if (inserted){
        qDebug() << "inserted score";
        QJsonObject newJson;
        QJsonArray tempArr;
        for(int i = 0; i < pos; i++){
            tempArr.push_back(json.value(JsonNames::players).toArray()[i].toObject());
        }
        QJsonObject player;
        player[JsonNames::name] = name;
        player[JsonNames::enemiesKilled] = enemiesKilled;
        tempArr.push_back(player);

        if(pos != numOfPlayers - 1){
            for(int i = pos+1; i < numOfPlayers; i++){
                tempArr.push_back(json.value(JsonNames::players).toArray()[i].toObject());
            }
        }
        newJson.insert(JsonNames::players, tempArr);
        qDebug() << newJson;
        save(newJson);
    }
    else{
        save(json);
    }



}

QJsonObject LeaderBoard::createNew()
{
    QJsonArray players;

    for(int i = 0; i < numOfPlayers; i++){
        QJsonObject player;
        player[JsonNames::name] = "Dima";
        player[JsonNames::enemiesKilled] = 3-i;
        players.push_back(player);
    }

    QJsonObject json;
    json.insert(JsonNames::players, players);
    return json;
}
