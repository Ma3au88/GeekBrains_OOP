#include "player.h"

Player::Player(const string& name) : GenericPlayer(name) {}

Player::~Player() {}

bool Player::IsHitting() const {
    cout << m_name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

void Player::Win() const {
    cout << m_name << " wins! \n";
}

void Player::Lose() const {
    cout << m_name << " loses! \n";
}

void Player::Push() const {
    cout << m_name << " pushes! \n";
}
