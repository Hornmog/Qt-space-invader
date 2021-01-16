#include "startdialog.h"
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include <QPushButton>

StartDialog::StartDialog() : QMessageBox()
{
    endlessMode = this->addButton("Endless", QMessageBox::ActionRole);
//    storyMode = this->addButton("Story", QMessageBox::ActionRole);
    leaderBoardMode = this->addButton("LeaderBoard", QMessageBox::ActionRole);
    quitbutton = this->addButton("Quit", QMessageBox::ActionRole);

    this->setEscapeButton(quitbutton);
    this->setText("Welcome! Chose one:");
}

int StartDialog::exec() {
    QMessageBox::exec();

    if (this->clickedButton() == endlessMode){
      return Mode::endless;
   }
//    else if (this->clickedButton() == storyMode){
//      return Mode::story;
//   }
    else if (this->clickedButton() == leaderBoardMode){
      return Mode::leaderBoard;
    }
    else if (this->clickedButton() == quitbutton){
      return Mode::quit;
    }
    return Mode::quit;
}
