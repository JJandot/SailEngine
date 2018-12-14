#include "island.h"

Island::Island() { label = 0; }

Island::Island(int labelId)
{
    label = labelId;
}

Island::Island(int labelId, QList<Resource> resources)
{
    label = labelId;
    addResources(resources);
}

void Island::addResources(QList<Resource> res)
{
    if(!resources.contains(res)) {
        res.append(res);
    }
}

void Island::addPixel(Pixel px)
{
    islandPixel.append(px);
}

int Island::getController() { return playerId; }

QList<Resource> Island::getResources() { return resources; }

int Island::getNbPixels()
{
    return islandPixel.size();
}

void Island::setLabel(int id) { label = id; }
void Island::setController(int _playerId) { playerId = _playerId; }
void Island::harvest(Resource r, int _value)
{
    r.addNbResources(-value);
}

