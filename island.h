#ifndef ISLAND_H
#define ISLAND_H

#include <QString>
#include <QList>
#include "resource.h"
#include "player.h"
#include "pixel.h"

class Island
{
public:
    Island();
    Island(int labelId);
    Island(int labelId, QList<Resource> resources);

    void harvest(Resource r);

    void addResources(QList<Resource> res);
    void addPixels(QList<Pixel> px);
    void addPixel(Pixel px);
    void setController(Player p);
    void setLabel(int id);

    Player getController();
    QList<Resource> getResources();

    int getNbPixels();

private:
    // engine
    int label;
    QList<Pixel> islandPixel;

    // gameplay
    QList<Resource> resources;
    Player controlledBy;

};

#endif // ISLAND_H
