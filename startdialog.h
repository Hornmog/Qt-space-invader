#ifndef STARTDIALOG_H
#define STARTDIALOG_H
#include <QMessageBox>
#include <QPushButton>

class StartDialog : QMessageBox
{
public:
    StartDialog();
    enum Mode {endless, story};

    int exec() override;

private:
    QPushButton *endlessMode;
    QPushButton *storyMode;
};

#endif // STARTDIALOG_H
