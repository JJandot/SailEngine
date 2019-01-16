#ifndef PLAYER_H
#define PLAYER_H

/*
 * Un joueur a un Id
 */

class Player
{
public:
    Player(int _id);
    int getId();

    int nbWood;
    int nbFood;

private:
    int id;
};

#endif // PLAYER_H
