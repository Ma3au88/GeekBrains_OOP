#include "game.h"

Game::Game(const vector<string>& names) {
    vector<string>::const_iterator pName;
    for (pName = names.begin(); pName != names.end(); ++pName) {
        m_Players.push_back(Player(*pName));
    }
    srand(static_cast<unsigned int>(time(0)));
    m_Deck.Populate();
    m_Deck.Shuffle();
}

Game::~Game() {}

void Game::Play() {
    vector<Player>::iterator pPlayer;
    for (int i = 0; i < 2; ++i) {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            m_Deck.Deal(*pPlayer);
        }
        m_Deck.Deal(m_House);
    }
    m_House.FlipFirstCard();
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
        cout << *pPlayer << endl;
    }
    cout << m_House << endl;
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
        m_Deck.AdditionalCards(*pPlayer);
    }
    m_House.FlipFirstCard();
    cout << endl << m_House;
    m_Deck.AdditionalCards(m_House);
    if (m_House.IsBoosted()) {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            if (!(pPlayer->IsBoosted())) {
                pPlayer->Win();
            }
        }
    } else {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            if (!(pPlayer->IsBoosted())) {
                if (pPlayer->GetTotal() > m_House.GetTotal()) {
                    pPlayer->Win();
                } else if (pPlayer->GetTotal() < m_House.GetTotal()) {
                    pPlayer->Lose();
                } else {
                    pPlayer->Push();
                }
            }
        }
    }
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
        pPlayer->Clear();
    }
    m_House.Clear();
}
