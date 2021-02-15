#ifndef METEORCOMMANDER_H
#define METEORCOMMANDER_H

#include <QObject>

class MeteorCommander : public QObject
{
    Q_OBJECT
public:
    explicit MeteorCommander(QObject *parent = nullptr);

signals:

};

#endif // METEORCOMMANDER_H
