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
    const int numOfPlayers = 3;
};

#endif // LEADERBOARD_H
