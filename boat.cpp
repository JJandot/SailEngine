#include "boat.h"

Boat::Boat(Team t)
{
    this->team = t;
    switch (t) {
        default:
            teamPath = "";
    }
}
