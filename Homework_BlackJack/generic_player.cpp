#include "generic_player.h"

GenericPlayer::GenericPlayer(const string& name) : m_name(name) {}

GenericPlayer::~GenericPlayer() {}

bool GenericPlayer::IsBoosted() const {
    return (GetTotal() > 21);
}

void GenericPlayer::Bust() const {
        cout << m_name << " busts! \n";
}

ostream& operator << (ostream& os, const GenericPlayer& aGenericPlayer) {
    os << aGenericPlayer.m_name << ":\t";
    vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_Cards.empty()) {
        for (pCard = aGenericPlayer.m_Cards.begin(); pCard != aGenericPlayer.m_Cards.end(); ++pCard) {
            os << *(*pCard) << "\t";
        }
        if (aGenericPlayer.GetTotal() != 0) {
            cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    } else {
        os << "<empty>";
    }
    return os;
}
