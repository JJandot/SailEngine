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
    Ship();
    Ship(Team t, QVector2D pos, QOpenGLWidget *mainWidget);
    void setDestination(QVector2D dest);
    QVector2D getDestination();
    void drawObject() override;
    Team getTeam();

    int getAttackPower() const;
    int getCapacityMax() const;
    int getStorage() const;

    int getOnIsland() const;

    void setOnIsland(int value);
    bool docked();

private:
    int controlledBy;

    float speed;
    QVector2D destination;

    std::string resourceName;
    int resourceCost;

    int attackPower;
    int capacityMax;
    int storage;

    int onIsland = -1;

    Team team;
    QString teamPath;
};

#endif // SHIP_H
