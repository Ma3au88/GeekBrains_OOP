/*
 * main.cpp
 * Homework #6
 * Created by Nikita Gusev
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Создать программу, которая считывает целое число типа int. И поставить «защиту от дурака»:
 * если пользователь вводит что-то кроме одного целочисленного значения, нужно вывести сообщение об ошибке
 * и предложить ввести число еще раз */

bool Check() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(2147483647, '\n');
        cerr << "You entered an incorrect number!" << endl;
        return false;
    } else
        return true;
}

/* Создать собственный манипулятор endll для стандартного потока вывода, который выводит два перевода строки и сбрасывает буфер */

ostream& endll(ostream& os) {
    os.put(os.widen('\n'));
    return (os << '\n');
}

class Card
{
public:
    enum suit { HEARTS, CLUBS, DIAMONDS, SPADES };
    enum rank { ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 10, QUEN = 10, KING = 10};
    friend ostream& operator << (ostream& os, const Card& aCard);   // Task #5
    Card (rank r = ACE, suit s = SPADES, bool ifu = true);
    int GetValue() const;
    void Flip();
private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

    Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) { }

    int Card::GetValue() const {
        int value = 0;
        if (m_IsFaceUp) {
            value = m_Rank;
            if (value > 10)
            {
                value = 10;
            }
            return value;
        }
    }

    void Card::Flip() {
        m_IsFaceUp = !(m_IsFaceUp);
    }

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

    Hand::Hand() {
        m_Cards.reserve(7);
    }

    Hand::~Hand() {
        Clear();
    }

    void Hand::Add(Card* pCard) {
        m_Cards.push_back(pCard);
    }

    void Hand::Clear() {
        vector<Card*>::iterator iter = m_Cards.begin();
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
            delete* iter;
            *iter = nullptr;
        }
        m_Cards.clear();
    }

    int Hand::GetTotal() const {
        if (m_Cards.empty()) {
            return 0;
        }
        int total = 0;
        vector<Card*>::const_iterator iter;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
            total += (*iter) -> GetValue();
        }
        bool containsAce = false;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
            if ((*iter) -> GetValue() == Card::ACE) {
                containsAce = true;
            }
        }
        if (containsAce && total <=11) {
            total += 10;
        }

        return total;
    }

class GenericPlayer : public Hand {
    friend ostream& operator << (ostream& os, const GenericPlayer& aGenericPlayer);     // Task #5
protected:
    string m_name;
public:
    GenericPlayer(const string& name = "");
    virtual ~GenericPlayer();
    virtual bool isHitting() const = 0;
    bool IsBoosted() const;
    void Bust() const;
};

    GenericPlayer::GenericPlayer(const string& name) : m_name(name) {}

    GenericPlayer::~GenericPlayer() {}

    bool GenericPlayer::IsBoosted() const {
        return (GetTotal() > 21);
    }

    void GenericPlayer::Bust() const {
            cout << m_name << " busts! \n";
    }

/* Реализовать класс Player, который наследует от класса GenericPlayer. У этого класса будет 4 метода:
    - virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса.
        Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false
    - void Win() const - выводит на экран имя игрока и сообщение, что он выиграл
    - void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл
    - void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью */

class Player : public GenericPlayer {
public:
    Player(const string& name = " ");
    virtual ~Player();
    virtual bool IsHitting() const;
    void Win() const;
    void Lose() const;
    void Push() const;
};

    Player::Player(const string& name) : GenericPlayer(name) {}

    Player::~Player() {}

    bool Player::IsHitting() const {
        cout << m_name << " , do you want a hit? (Y/N): ";
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

/* Реализовать класс House, который представляет дилера. Этот класс наследует от класса GenericPlayer. У него есть 2 метода:
    - virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта.
        Если у дилера не больше 16 очков, то он берет еще одну карту
    - void FlipFirstCard() - метод переворачивает первую карту дилера */

class House : public GenericPlayer {
public:
    House(const string& name = "House");
    virtual ~House();
    virtual bool IsHitting() const;
    void FlipFirstCard();
};

    House::House(const string& name) : GenericPlayer(name) {}

    House::~House() {}

    bool House::IsHitting() const {
        return (GetTotal() <= 16);
    }

    void House::FlipFirstCard() {
        if (!(m_Cards.empty())) {
            m_Cards[0] -> Flip();
        } else {
            cout << "No card to flip! \n";
        }
    }

/* Написать перегрузку оператора вывода для класса Card. Если карта перевернута рубашкой вверх (мы ее не видим),
 * вывести ХХ, если мы ее видим, вывести масть и номинал карты. Также для класса GenericPlayer написать перегрузку оператора вывода,
 * который должен отображать имя игрока и его карты, а также общую сумму очков его карт */

ostream& operator << (ostream& os, const Card& aCard) {
    const string RANKS[] = {"0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const string SUITS[] = {"c", "d", "h", "s"};

    if (aCard.m_IsFaceUp) {
        os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
    } else {
        os << "XX";
    }
    return os;
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

int main()
{
    cout << "Task #1" << endll;

    int number;
    bool check;

    do {
        cout << "Please enter an integer number: ";
        cin >> number;
        check = Check();
    } while (check == false);

    cout << endl << "Task #2" << endll;

    cout << "Test: endll" << endll;

    return 0;
}
