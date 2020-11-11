#ifndef LEADERBOXWINDOW_H
#define LEADERBOXWINDOW_H

#include <QMessageBox>



class LeaderBoardWindow : public QMessageBox
{
public:
    LeaderBoardWindow();
    void setLeaderboard(QJsonObject leaderboard);
    //int exec() override;
};

#endif // LEADERBOXWINDOW_H
