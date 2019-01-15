#ifndef ISLAND_H
#define ISLAND_H

#include <QString>
#include <QList>
#include "resource.h"
#include "player.h"
#include "pixel.h"

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
    Island(int labelId, QList<Resource> resources);

    void harvest(Resource r, int _value);

    void addResources(QList<Resource> res);
    void addPixels(QList<Pixel> px);
    void addPixel(Pixel px);
    void removeAllPixels();
    void setController(int _playerId);
    void setLabel(int id);

    int getController();
    QList<Resource> getResources();

    int getNbPixels();

private:
    // engine
    int label;
    QList<Pixel> islandPixel;

    // gameplay
    QList<Resource> resources;
    int playerId;

};

#endif // ISLAND_H
