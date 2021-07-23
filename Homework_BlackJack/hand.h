#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>

class Hand {
protected:
    vector<Card*> m_Cards;
public:
    Hand();
    virtual ~Hand();

    void Add(Card* pCard);
    void Clear();
    int GetTotal() const;
};

#endif // HAND_H
