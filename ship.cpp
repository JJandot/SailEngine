#include "ship.h"

Ship::Ship(){}

Ship::Ship(Team t, QVector2D pos, QOpenGLWidget *mainWidget) : Object (mainWidget)
{
    this->team = t;
    switch (team) {
        case Team::BLACK:
            teamPath = ":/img/teams/black/";
            break;
        case Team::BLUE:
            teamPath = ":/img/teams/blue/";
            break;
        case Team::GREEN:
            teamPath = ":/img/teams/green/";
            break;
        case Team::RED:
            teamPath = ":/img/teams/red/";
            break;
        case Team::WHITE:
            teamPath = ":/img/teams/white/";
            break;
        case Team::YELLOW:
            teamPath = ":/img/teams/yellow/";
            break;
        default:
            teamPath = "";
            break;
    }
    destination = QVector2D(-1, -1);
    teamPath += "ship.png";
    setSprite(teamPath);
    this->pos = pos;
    attackPower = 10;

}

void Ship::setDestination(QVector2D dest){
    destination.setX(dest.x());
    destination.setY(dest.y());
}

void Ship::drawObject() {
    if(destination.x() != -1){
        if(pos.x() < destination.x() - 2)
            pos.setX(pos.x() + 3);
        else if(pos.x() > destination.x() + 2)
            pos.setX(pos.x() - 3);
        if(pos.y() < destination.y() - 2)
            pos.setY(pos.y() + 3);
        else if(pos.y() > destination.y() + 2)
            pos.setY(pos.y() - 2);
    }
    label->setGeometry(pos.x(), pos.y(), width, height);
    label->setPixmap(img);
}

bool Ship::docked(){
    return pos.x() >= destination.x() - 2 &&
            pos.x() <= destination.x() + 2 &&
            pos.y() >= destination.y() - 2 &&
            pos.y() <= destination.y() + 2 &&
            onIsland;
}

QVector2D Ship::getDestination(){
    return destination;
}

Team Ship::getTeam(){
    return team;
}

int Ship::getAttackPower() const
{
    return attackPower;
}

int Ship::getCapacityMax() const
{
    return capacityMax;
}

int Ship::getStorage() const
{
    return storage;
}

void Ship::addStorage(int value) {
    storage += value;
    if(storage > getCapacityMax())
        storage = capacityMax;
}


void Ship::setAttackPower(int value) {
    attackPower = value;
}
void Ship::setCapacityMax(int value) {
    capacityMax = value;
}


int Ship::getOnIsland() const
{
    return onIsland;
}

void Ship::setOnIsland(int value)
{
    onIsland = value;
}
