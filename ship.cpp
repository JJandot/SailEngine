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

    teamPath += "ship.png";
    setSprite(teamPath);
    this->pos = pos;

}
