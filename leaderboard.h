#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class LeaderBoard : public QFile
{
public:
    LeaderBoard();
    QJsonObject load();
    void save(QJsonObject obj);
    void update(QString name, int enemiesKilled);
    QJsonObject createNew();

private:
    QJsonObject createPlayer(QString name = "blank", int enemiesKilled = 0);

    const int numOfPlayers = 3;
};

#endif // LEADERBOARD_H
