#ifndef CHECKTEXT_H
#define CHECKTEXT_H

#include <QObject>
#include <QGraphicsTextItem>
#include "consts.h"

class CheckText : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit CheckText()  : QGraphicsTextItem() {
    }
    int type() const override {return TypeIndex::checkText;}
signals:

};

#endif // CHECKTEXT_H
