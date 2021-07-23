#ifndef GENERIC_PLAYER_H
#define GENERIC_PLAYER_H

#include "hand.h"
#include <string>

class GenericPlayer : public Hand {
    friend ostream& operator << (ostream& os, const GenericPlayer& aGenericPlayer);
protected:
    string m_name;
public:
    GenericPlayer(const string& name = "");
    virtual ~GenericPlayer();
    virtual bool IsHitting() const = 0;
    bool IsBoosted() const;
    void Bust() const;
};

ostream& operator << (ostream& os, const GenericPlayer& aGenericPlayer);


#endif // GENERIC_PLAYER_H
