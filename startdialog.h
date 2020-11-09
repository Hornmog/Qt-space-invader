#ifndef STARTDIALOG_H
#define STARTDIALOG_H
#include <QMessageBox>
#include <QPushButton>

class StartDialog : QMessageBox
{
public:
    StartDialog();
    enum Mode {endless, story, leaderBoard, quit};

    int exec() override;

private:
    QPushButton *endlessMode;
    QPushButton *storyMode;
    QPushButton *leaderBoardMode;
    QPushButton *quitbutton;
};

#endif // STARTDIALOG_H
