#ifndef BASE_H
#define BASE_H

/*
 * Les bases sont liées à une île (islandId)
 * La base appartient à un joueur, sinon playerId = -1
 * Si la base n'a plus de point de vie, alors le joueur n'a plus l'île (controlled = false, playerId = -1)
 * On peut les attaquer ou les réparer
 */

class Base
{
public:
    Base(int _id, int _islandId, int _maxLife);

    void setPlayerId(int _playerId);
    void attack(int _value);
    void repair(int _value);

    int getLife();
    int getPlayerId();

    bool isControlled();
private:
    int id;
    int islandId;
    int playerId;

    int life;
    int maxLife;

    bool controlled;
};

#endif // BASE_H
