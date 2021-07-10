/*
 * main.cpp
 * Homework #3
 * Created by Nikita Gusev
 */

#include <iostream>
#include <math.h>
#include <string>

using namespace std;

/* Создать абстрактный класс Figure (фигура). Его наследниками являются классы Parallelogram (параллелограмм) и Circle (круг).
 * Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат), Rhombus (ромб).
 * Для всех классов создать конструкторы. Для класса Figure добавить чисто виртуальную функцию area() (площадь).
 * Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади */

class Figure
{
public:
    virtual int area() const = 0;
};

class Parallelogram : public Figure
{
    int value_height;
    int value_length;
public:
    Parallelogram (int height = 0, int length = 0)
    : value_height(height), value_length(length) {}

    int area() const
    {
        return value_height * value_length;
    }

};

class Circle : public Figure
{
    int value_radius;
    const double pi = 3.14159265358979323846;
public:
    Circle(int radius = 0)
        : value_radius(radius) {}

    int area() const
    {
        return pi * pow(value_radius,2);
    }
};

class Rectangle : public Parallelogram
{
public:
    Rectangle(int height = 0, int length = 0)
        :Parallelogram(height, length) {}
};

class Square : public Parallelogram
{
public:
    Square(int height = 0)
        :Parallelogram(height, height) {}
};

class Rhombus : public Parallelogram
{
public:
    Rhombus(int height = 0, int length = 0)
        :Parallelogram(height, length) {}
};

/* Создать класс Car (автомобиль) с полями company (компания) и model (модель).
 * Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус). От этих классов наследует класс Minivan (минивэн).
 * Создать конструкторы для каждого из классов, чтобы они выводили данные о классах.
 * Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы.
 * Обратить внимание на проблему «алмаз смерти» */

class Car
{
protected:
    string name_company;
    string name_model;
public:
    Car(string company = "", string model = "")
        :name_company(company), name_model(model)
    {
        cout << "Car " << name_company << ", " << name_model << endl;
    }

};

class PassengerCar: virtual public Car
{
public:
    PassengerCar(string company = "", string model = "")
        :Car(company, model)
    {
        cout << "PassengerCar " << name_company << ", " << name_model << endl;
    }
};

class Bus: virtual public Car
{
public:
    Bus(string company = "", string model = "")
        :Car(company, model)
    {
        cout << "Bus " << name_company << ", " << name_model << endl;
    }
};

class Minivan: public PassengerCar, public Bus
{
public:
    Minivan(string company = "", string model = "")
        :Car(company, model), PassengerCar(company, model), Bus (company, model)
    {
        cout << "Minivan " << name_company << ", " << name_model << endl;
    }
};

/* Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2).
 * Предусмотреть, чтобы знаменатель не был равен 0. Перегрузить:
    - математические бинарные операторы (+, -, *, /) для выполнения действий с дробями
    - унарный оператор (-)
    - логические операторы сравнения двух дробей (==, !=, <, >, <=, >=).
   Продемонстрировать использование перегруженных операторов */

class Fraction
{
protected:
    double value_numerator;
    double value_denominator;

public:
    Fraction(int numerator, int denominator)
    {
        if (denominator != 0)
        {
            value_numerator = numerator;
            value_denominator = denominator;
        }
        else throw runtime_error("Denominator can't be NULL!");
    }

    friend Fraction operator+(const Fraction& d1, const Fraction& d2);
    friend Fraction operator-(const Fraction& d1, const Fraction& d2);
    friend Fraction operator*(const Fraction& d1, const Fraction& d2);
    friend Fraction operator/(const Fraction& d1, const Fraction& d2);
    friend bool operator> (const Fraction& d1, const Fraction& d2);
    friend bool operator>= (const Fraction& d1, const Fraction& d2);
    friend bool operator<(const Fraction& d1, const Fraction& d2);
    friend bool operator<=(const Fraction& d1, const Fraction& d2);

    int getNumerator() const {
        return value_numerator;
    }
    int getDenominator() const {
        return value_denominator;
    }

    Fraction operator-() const
    {
        return Fraction(-value_numerator, value_denominator);
    }
};

    Fraction operator+ (const Fraction& d1, const Fraction& d2)
    {
        return Fraction((d1.value_numerator * d2.value_denominator + d2.value_numerator * d1.value_denominator), d1.value_denominator * d2.value_denominator);
    }

    Fraction operator- (const Fraction& d1, const Fraction& d2)
    {
        return Fraction((d1.value_numerator * d2.value_denominator - d2.value_numerator * d1.value_denominator), d1.value_denominator * d2.value_denominator);
    }

    Fraction operator* (const Fraction& d1, const Fraction& d2)
    {
        return Fraction(d1.value_numerator * d2.value_numerator, d1.value_denominator * d2.value_denominator);
    }

    Fraction operator/ (const Fraction& d1, const Fraction& d2)
    {
        return Fraction(d1.value_numerator * d2.value_denominator, d1.value_denominator * d2.value_numerator);
    }

    bool operator> (const Fraction& d1, const Fraction& d2)
    {
        return ((d1.value_numerator / d1.value_denominator) > (d2.value_numerator / d2.value_denominator));
    }

    bool operator>= (const Fraction& d1, const Fraction& d2)
    {
        return ((d1.value_numerator / d1.value_denominator) >= (d2.value_numerator / d2.value_denominator));
    }

    bool operator<(const Fraction& d1, const Fraction& d2)
    {
        return !((d1.value_numerator / d1.value_denominator) >= (d2.value_numerator / d2.value_denominator));
    }

    bool operator<=(const Fraction& d1, const Fraction& d2)
    {
        return !((d1.value_numerator / d1.value_denominator) > (d2.value_numerator / d2.value_denominator));
    }

/* Создать класс Card, описывающий карту в игре БлэкДжек. У этого класса должно быть три поля:
 * масть, значение карты и положение карты (вверх лицом или рубашкой). Сделать поля масть и значение карты типом перечисления (enum).
 * Положение карты - тип bool. Также в этом классе должно быть два метода:
 *  - метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
    - метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1 */

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

int main()
{
    cout << "Task #1" << endl << endl;

    Circle circle(3);
    cout << "The area of the circle is: " << circle.area() << endl;
    Rectangle rectangle(4, 6);
    cout << "The area of the rectangle is: " << rectangle.area() << endl;
    Square square(7);
    cout << "The area of the square is: " << square.area() << endl;
    Rhombus rhombus(2, 9);
    cout << "The area of the rhombus is: " << rhombus.area() << endl;

    cout << endl << "Task #2" << endl << endl;

    Car Car("Kia", "Rio");
    cout << endl;
    PassengerCar  PassengerCar("Citroen", "C4");
    cout << endl;
    Bus Bus("Volvo", "9700");
    cout << endl;
    Minivan("Opel", "Zafira Life");
    cout << endl;

    cout << endl << "Task #3" << endl << endl;

    Fraction fraction1(7, 13);
    Fraction fraction2(3, 9);

    Fraction FractionSum = fraction1 + fraction2;
    cout << "Sum: " << FractionSum.getNumerator() << "/" << FractionSum.getDenominator() << endl;
    Fraction FractionDifference = fraction1 - fraction2;
    cout << "Difference: " << FractionDifference.getNumerator() << "/" << FractionDifference.getDenominator() << endl;
    Fraction FractionMultiplication = fraction1 * fraction2;
    cout << "Multiplication: " << FractionMultiplication.getNumerator() << "/" << FractionMultiplication.getDenominator() << endl;
    Fraction FractionDivision = fraction1 / fraction2;
    cout << "Division: " << FractionDivision.getNumerator() << "/" << FractionDivision.getDenominator() << endl;
    Fraction FractionMinus = -fraction1;
    cout << "Minus: " << FractionMinus.getNumerator() << "/" << FractionMinus.getDenominator() << endl;

    if (fraction1 > fraction2)
    {
        cout << "fraction1 > fraction2" << endl;
    }
    if (fraction1 < fraction2)
    {
        cout << "fraction1 < fraction2" << endl;
    }
    if (fraction1 >= fraction2)
    {
        cout << "fraction1 >= fraction2" << endl;
    }
    if (fraction1 <= fraction2)
    {
        cout << "fraction1 <= fraction2" << endl;
    }

    return 0;
}
