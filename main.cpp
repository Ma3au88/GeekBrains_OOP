/*
 * main.cpp
 * Homework #4
 * Created by Nikita Gusev
 */

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>


using namespace std;

class ArrayInt {
    int m_length;
    int* m_data;
public:
    ArrayInt() : m_length(0), m_data(nullptr) {}

    ArrayInt(int length) : m_length(length) {
        assert(length >= 0);
        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    ~ArrayInt() {
        delete [] m_data;
    }

    void erase() {
        delete [] m_data;
        m_data = nullptr;
        m_length = 0;
    }

    int getLength () const {
        return m_length;
    }

    int& operator[] (int index) {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void resize(int newLength) {
        if (m_length == newLength)
            return;
        if (newLength <= 0) {
            erase();
            return;
        }
        int* data = new int[newLength];
        if (m_length > 0) {
            int elementsToCopy = newLength > m_length ? m_length : newLength;
            for (int index = 0; index < elementsToCopy; index++) {
                data[index] = m_data[index];
            }
        }
        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index) {
        assert(index >= 0 && index <= m_length);
        int* data = new int[m_length + 1];
        for (int i = 0; i < index; ++i)
            data[i] = m_data[i];
        data[index] = value;
        for (int i = index; i < m_length; ++i)
            data[i + 1] = m_data[i];

        delete [] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value) {
        insertBefore(value, m_length);
    }

/* Добавить в контейнерный класс, который был написан в этом уроке, методы:
•	для удаления последнего элемента массива (аналог функции pop_back() в векторах)
•	для удаления первого элемента массива (аналог pop_front() в векторах)
•	для сортировки массива
•	для вывода на экран элементов */

    void pop_back() {
        if (m_length > 1) {
            int *data = new int[m_length - 1];
            for (int before = 0; before < m_length - 1; ++before)
                data[before] = m_data[before];
            delete [] m_data;
            m_data = data;
            --m_length;
        } else {
            delete [] m_data;
            --m_length;
        }
    }

    void pop_front() {
        if (m_length > 1) {
            int *data = new int[m_length - 1];
            for (int before = 1; before < m_length; ++before)
                data[before - 1] = m_data[before];
            delete [] m_data;
            m_data = data;
            --m_length;
        } else {
            delete [] m_data;
            --m_length;
        }
    }

    void sort() {
        int temp;
        for (int i = 0; i < m_length; i++) {
            temp = m_data[i];
            for (int j = i; j < m_length; j++)
                if (temp > m_data[j]) {
                    temp = m_data[j];
                    m_data[j] = m_data[i];
                    m_data[i] = temp;
                }
        }
    }

    void print() const {
        for (int i = 0; i < m_length; i++) {
            cout << m_data[i] << " ";
        }
        cout << endl;
    }
};

/* Дан вектор чисел, требуется выяснить, сколько среди них различных.
 * Постараться использовать максимально быстрый алгоритм */

void printV(vector<int>& v) {
    vector<int> :: iterator it;
    for (it = v.begin(); it != (v.begin(), v.end()); it++) {
        cout << *it << " ";
    }
}

/* Реализовать класс Hand, который представляет собой коллекцию карт. В классе будет одно поле:
 * вектор указателей карт (удобно использовать вектор, т.к. это по сути динамический массив,
 * а тип его элементов должен быть - указатель на объекты класса Card). Также в классе Hand должно быть 3 метода:
•	метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве параметра
указатель на новую карту
•	метод Clear, который очищает руку от карт
•	метод GetValue, который возвращает сумму очков карт руки (здесь предусмотреть возможность того, что туз может быть равен 11) */

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
            *iter = 0;
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


int main()
{
    cout << "Task #1" << endl << endl;

    ArrayInt NumberOne(20);
    for (int i = 0; i < NumberOne.getLength(); ++i) {
        NumberOne[i] = i;
    }
    NumberOne.print();
    NumberOne.pop_back();
    NumberOne.print();
    NumberOne.pop_front();
    NumberOne.print();

    ArrayInt NumberTwo(3);
    NumberTwo[0] = 4;
    NumberTwo[1] = 7;
    NumberTwo[2] = 3;
    NumberTwo.print();
    NumberTwo.sort();
    NumberTwo.print();

    cout << endl << "Task #2" << endl << endl;

    cout << "This is a vector of numbers: ";
    vector<int> v{2, 5, 5, 7, 9, 1, 3, 9, 4, 0, 8, 7, 1};
    printV(v);
    cout << endl;
    cout << "Let's sort the vector by removing the duplicate numbers: ";
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    printV(v);
    cout << "\n" << "Different numbers: " << v.size() << endl;

    return 0;
}
