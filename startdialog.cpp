#include "startdialog.h"
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include <QPushButton>

StartDialog::StartDialog() {
    endlessMode = this->addButton("Endless", QMessageBox::ActionRole);
    storyMode = this->addButton("Story", QMessageBox::ActionRole);
    // Why did you disable the story mode?
    leaderBoardMode = this->addButton("LeaderBoard", QMessageBox::ActionRole);
    quitbutton = this->addButton("Quit", QMessageBox::ActionRole);

    this->setEscapeButton(quitbutton);
    this->setText("Welcome! Choose one:");
}

int StartDialog::exec() {
    QMessageBox::exec();

    if (this->clickedButton() == endlessMode){
      return Mode::endless;
    }
    else if (this->clickedButton() == storyMode){
      return Mode::story;
    }
    else if (this->clickedButton() == leaderBoardMode){
      return Mode::leaderBoard;
    }
    else if (this->clickedButton() == quitbutton){
      return Mode::quit;
    }
    return Mode::quit;
}
