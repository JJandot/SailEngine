#ifndef BOAT_H
#define BOAT_H

#include "object.h"
#include "teams.h"

class Object;

class Boat : public Object
{
public:
    Boat(Team t);

private:
    Team team;
    QString teamPath;
};

#endif // BOAT_H
