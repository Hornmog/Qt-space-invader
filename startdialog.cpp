#include "startdialog.h"
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include <QPushButton>

StartDialog::StartDialog() : QMessageBox()
{
    endlessMode = this->addButton("Endless", QMessageBox::ActionRole);
    storyMode = this->addButton("Story", QMessageBox::ActionRole);

    this->setText("Choose mode: ");
    //msgBox.setInformativeText("Do you want to save your changes?");
}

int StartDialog::exec() {
    QMessageBox::exec();

    if (this->clickedButton() == endlessMode){
          return Mode::endless;
       }
    else if (this->clickedButton() == storyMode){
          return Mode::story;
       }
}
