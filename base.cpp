#include "base.h"

Base::Base(int _id, int _islandId, int _maxLife)
{
    id = _id;
    islandId = _islandId;
    maxLife = _maxLife;
    life = maxLife;
    playerId = -1;

    controlled = false;
}

void Base::setPlayerId(int _playerId)
{
    playerId = _playerId;
    if(playerId > 0)
        controlled = true;
}

void Base::attack(int _value)
{
    life -= _value;
    if(life < 0) {
        life = 0;
        controlled = false;
        setPlayerId(-1);
    }
}

void Base::repair(int _value)
{
    life += _value;
    if(life > maxLife)
        life = maxLife;
}

int Base::getLife() {
    return life;
}

int Base::getPlayerId() {
    return playerId;
}

bool Base::isControlled() {
    return controlled;
}
