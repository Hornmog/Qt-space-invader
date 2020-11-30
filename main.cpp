#include <QApplication>
#include "gamemanager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameManager* manager = new GameManager();
    return a.exec();
}
