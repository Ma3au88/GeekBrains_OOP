#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

class Card
{
public:
    enum suit { HEARTS, CLUBS, DIAMONDS, SPADES };
    enum rank { ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 10, QUEN = 10, KING = 10};
    friend ostream& operator << (ostream& os, const Card& aCard);
    Card (rank r = ACE, suit s = SPADES, bool ifu = true);
    int GetValue() const;
    void Flip();
private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

#endif // CARD_H
