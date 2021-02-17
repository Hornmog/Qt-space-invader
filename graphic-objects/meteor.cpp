#include "meteor.h"
#include <QRandomGenerator>
#include "consts.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QDebug>
Meteor::Meteor()
{
    CoordPair diff(0.2 * period_ms, 0.02 * period_ms);

    speed.x = QRandomGenerator::global()->bounded(diff.x * 2 + 1) - diff.x;
    speed.y = QRandomGenerator::global()->bounded(diff.y * 2 + 1) - diff.y;
    size.x = QRandomGenerator::global()->bounded(50, 100);
    size.y = QRandomGenerator::global()->bounded(50, 100);

    if(speed.x >= 0){
        currPos.x = -size.x;
    }
    else{
        currPos.x = sceneWidth;
    }
    currPos.y = QRandomGenerator::global()->bounded(int(sceneHeight*0.25), int(sceneHeight - size.y));
    this->setZValue(ScenePriority::meteor);
    int rand = QRandomGenerator::global()->bounded(ImagePaths::meteor.size());
    QPixmap image(ImagePaths::meteor[rand]);
    this->setPixmap(image.scaled(size.x, size.y, Qt::KeepAspectRatio));
}


void Meteor::move()
{
    if((speed.x < 0 && x() > sceneWidth) || (speed.x > 0 && x() < -boundingRect().x())){
        delete this;
    }
    currPos.x += speed.x;
    currPos.y += speed.y;
    setPos(currPos.x,currPos.y);
    groupCheckTextInfo();
}

void Meteor::groupCheckTextInfo()
{
    QString output = "";
    output += "SpeedX: " + QString::number(speed.x) + " speedY: " + QString::number(speed.y) + "\n";
    checkText->setPlainText(output);
}

void Meteor::onTimer()
{
    groupCheckTextInfo();

    if((bulletCollisionCheck() != Side::nobody)){
        selfDestroy();
    }
    else{
        move();
        checkText->setPos(x(),y());
    }
}

void Meteor::selfDestroy()
{
    delete this;
}

void Meteor::addToScene(QGraphicsScene *scene)
{
    scene->addItem(this);
    this->setPos(currPos.x, currPos.y);
}

