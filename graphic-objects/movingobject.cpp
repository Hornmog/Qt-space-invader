#include "movingobject.h"
#include "bullet.h"

bool MovingObject::checkTextVisible = false;

MovingObject::MovingObject(QObject *parent) : QObject(parent)
{
    checkText = new CheckText();
    setUpCheckText();

    mainTimer = new Timer();
    connect(mainTimer, &QTimer::timeout, this, &MovingObject::onTimer);
    mainTimer->start(period_ms);

}

MovingObject::~MovingObject()
{
    mainTimer->stop();
    delete checkText;
}

void MovingObject::addToScene(QGraphicsScene *scene)
{
    scene->addItem(this);
    scene->addItem(checkText);

}

QGraphicsItem* MovingObject::collisionCheck(int typeIndex)
{
    auto items = this->collidingItems();
    for (QGraphicsItem* item: qAsConst(items)) {
        if(item->type() == typeIndex){
            return item;
        }
    }
    return nullptr;
}

int MovingObject::bulletCollisionCheck()
{
     auto item = collisionCheck(TypeIndex::bullet);
     if(item != nullptr) {
        Bullet* bullet = static_cast<Bullet*>(item);
        int bulletSide = bullet->side;
        bullet->deleteSelf();
        return bulletSide;
    }
    return Side::nobody;
}

void MovingObject::setUpCheckText()
{

    QFont font = QFont("Impact", 16, QFont::Bold);
    QColor color = QColor(255, 100, 108);
    checkText->setFont(font);
    checkText->setDefaultTextColor(color);
    checkText->setPlainText(QString::number(0));
    checkText->setZValue(ScenePriority::text);
    checkText->setVisible(checkTextVisible);
}


void MovingObject::toggleCheckText()
{
    qDebug() << "Check Text visible 1: " << checkTextVisible;
    checkText->setVisible(checkTextVisible);
    qDebug() << "Check Text visible 2: " << checkText->isVisible();

}
