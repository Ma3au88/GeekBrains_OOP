/*
 * main.cpp
 * Homework #5
 * Created by Nikita Gusev
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами */

template <class T>
class Pair1 {
    T m_first;
    T m_second;
public:
    Pair1(const T& first, const T& second) : m_first(first), m_second(second) {}

    const T& first() const {
        return m_first;
    }
    const T& second() const {
        return m_second;
    }
};

/* Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах */

template <class T1, class T2>
class Pair {
    T1 m_first;
    T2 m_second;
public:
    Pair(const T1& first, const T2& second) : m_first(first), m_second(second) {}

    const T1& first() const {
        return m_first;
    }
    const T2& second() const {
        return m_second;
    }
};

/* Написать шаблон класса StringValuePair, в котором первое значение всегда типа string,
 * а второе — любого типа. Этот шаблон класса должен наследовать частично специализированный класс Pair,
 * в котором первый параметр — string, а второй — любого типа данных */

template <class T3>
class StringValuePair : public Pair <string, T3> {
public:
    StringValuePair(const string& word, const T3& number) : Pair<string, T3>(word, number) {}
};

/* Согласно иерархии классов, которая представлена в методичке к уроку 3, от класса Hand наследует класс GenericPlayer,
 * который обобщенно представляет игрока, ведь у нас будет два типа игроков - человек и компьютер.
 * Создать класс GenericPlayer, в который добавить поле name - имя игрока. Также добавить 3 метода:
    - IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта
    - IsBoosted() - возвращает bool значение, есть ли у игрока перебор
    - Bust() - выводит на экран имя игрока и объявляет, что у него перебор */

class Card
{
public:
    enum suit { HEARTS, CLUBS, DIAMONDS, SPADES };
    enum rank { ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 10, QUEN = 10, KING = 10};

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

int main()
{
    cout << "Task #1" << endl << endl;

    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    cout << endl << "Task #2" << endl << endl;

    Pair<int, double> p3(6, 7.8);
    cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';

    const Pair<double, int> p4(3.4, 5);
    cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

    cout << endl << "Task #3" << endl << endl;

    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    return 0;
}
