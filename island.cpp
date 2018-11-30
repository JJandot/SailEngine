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

}

void Island::addPixel(Pixel px)
{
    islandPixel.append(px);
}

Player Island::getController() { return controlledBy; }

QList<Resource> Island::getResources() { return resources; }

int Island::getNbPixels()
{
    return islandPixel.size();
}

void Island::setLabel(int id) { label = id; }
void Island::setController(Player p) { controlledBy = p; }
void Island::harvest(Resource r)
{
}

void Island::addPixels(QList<Pixel> px)
{
}
