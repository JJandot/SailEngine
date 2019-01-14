#ifndef SHIP_H
#define SHIP_H

#include <QVector2D>
#include <string>
#include "object.h"
#include "teams.h"

/*
 * Un bateau appartient à un joueur
 * il a une vitesse, un coût de fabrication, une destination
 * 2 types : transport (ressource, quantité), combat (dégats, range)
 */

class Ship : public Object
{
public:
    Ship(Team t, QVector2D pos);

private:
    int controlledBy;

    float speed;
    QVector2D destination;

    std::string resourceName;
    int resourceCost;

    Team team;
    QString teamPath;
};

#endif // SHIP_H
