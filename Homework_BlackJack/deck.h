#ifndef DECK_H
#define DECK_H

#include "generic_player.h"
#include "hand.h"

class Deck : public Hand {
public:
    Deck();
    virtual ~Deck();
    void Populate();
    void Shuffle();
    void Deal(Hand& aHand);
    void AdditionalCards(GenericPlayer& aGenericPlayer);
};

#endif // DECK_H
