#ifndef SHIP_H
#define SHIP_H

#include <QVector2D>
#include <string>

/*
 * Un bateau appartient à un joueur
 * il a une vitesse, un coût de fabrication, une destination
 * 2 types : transport (ressource, quantité), combat (dégats, range)
 */

class Ship
{
public:
    Ship();

private:
    int controlledBy;

    float speed;
    QVector2D destination;

    std::string resourceName;
    int resourceCost;
};

#endif // SHIP_H
