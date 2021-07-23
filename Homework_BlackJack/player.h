#ifndef PLAYER_H
#define PLAYER_H

#include "generic_player.h"

class Player : public GenericPlayer {
public:
    Player(const string& name = " ");
    virtual ~Player();
    virtual bool IsHitting() const;
    void Win() const;
    void Lose() const;
    void Push() const;
};

#endif // PLAYER_H
