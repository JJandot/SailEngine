#ifndef ISLAND_H
#define ISLAND_H

#include <iostream>
#include <QOpenGLWidget>
#include <QString>
#include <QList>
#include <QLabel>
#include "resource.h"
#include "player.h"
#include "pixel.h"
#include "teams.h"

/*
 * Les îles ont un label attribué en fonction de la islandMap
 * et une liste des pixels qui lui appartiennent
 * Chaque île a une liste de ressources
 * On peut ajouter des ressources, les récolter
 * Chaque île appartient à un joueur, sinon playerId = -1
 */

class Island
{
public:
    Island();
    Island(int labelId);
    Island(int labelId, Resource *res);

    void harvest(int _value);

    void addResource(int value);
    void addPixels(QList<Pixel> px);
    void addPixel(Pixel px);
    void removeAllPixels();
    void setController(Team playerTeam);
    void setLabel(int id);
    void setResource(Resource *res);

    Team getController();
    Resource* getResource();

    int getNbPixels();
    void setQLabel(QOpenGLWidget *mainWidget);
    void setPath(QString path);
    void drawFlag();
    void drawResource();
    Pixel getPosition();


    int getAttackPower() const;

private:
    // engine
    int label;
    QList<Pixel> islandPixel;
    QLabel *qlabel;
    QLabel *qlabelR;
    QPixmap img;
    // gameplay
    Resource *resource;
    //int playerId;
    Team team;
    int attackPower;

};

#endif // ISLAND_H
