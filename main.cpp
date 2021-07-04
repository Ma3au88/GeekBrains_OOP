/*
 * main.cpp
 * Homework #1
 * Created by Nikita Gusev
 */

#include <iostream>
#include <math.h>
#include <cstdint>

using namespace std;

    /* Создать класс Power, который содержит два вещественных числа. Этот класс должен иметь
    две переменные-члена для хранения этих вещественных чисел. Еще создать два метода:
    один с именем set, который позволит присваивать значения переменным, второй — calculate,
    который будет выводить результат возведения первого числа в степень второго числа. Задать
    значения этих двух чисел по умолчанию. */

class Power
{
    double a = 0;
    double b = 0;
public:
    Power() {}

    void set(double base, double exponent)
    {
        a = base;
        b = exponent;
    }

    void calculate()
    {
       cout << a << "^" << b << " = " << pow(a, b) << endl;
    }
};

    /* Написать класс с именем RGBA, который содержит 4 переменные-члена типа std::uint8_t:
    m_red, m_green, m_blue и m_alpha (#include cstdint для доступа к этому типу). Задать 0 в
    качестве значения по умолчанию для m_red, m_green, m_blue и 255 для m_alpha. Создать
    конструктор со списком инициализации членов, который позволит пользователю передавать
    значения для m_red, m_blue, m_green и m_alpha. Написать функцию print(), которая будет
    выводить значения переменных-членов. */

class RGBA
{   // Заменил unit8_t на unit16_t, т.к. в консоль выводил непонятные символы
    std::uint16_t m_red = 0;
    std::uint16_t m_green = 0;
    std::uint16_t m_blue = 0;
    std::uint16_t m_alpha = 255;
public:
    RGBA() {}
    RGBA (std::uint16_t red, std::uint16_t green, std::uint16_t blue, std::uint16_t alpha) :
        m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {}

    void print()
    {
        cout << endl << "red: " << m_red << ", green: " << m_green << ", blue: " << m_blue << ", alpha: " << m_alpha << endl;
    }
};

    /* Написать класс, который реализует функциональность стека. Класс Stack должен иметь:
    - private-массив целых чисел длиной 10;
    - private целочисленное значение для отслеживания длины стека;
    - public-метод с именем reset(), который будет сбрасывать длину и все значения
    элементов на 0;
    - public-метод с именем push(), который будет добавлять значение в стек. push()
    должен возвращать значение false, если массив уже заполнен, и true в противном
    случае;
    - public-метод с именем pop() для вытягивания и возврата значения из стека. Если в
    стеке нет значений, то должно выводиться предупреждение;
    - public-метод с именем print(), который будет выводить все значения стека. */

class Stack
{
    int array[10];
    int length = 0;
public:
    Stack() {}

    void reset()
    {
        while (length)
            array[length--] = 0;
    }

    bool push(int Number)
    {
        if (length > 9)
            return false;
        else
            array[length++] = Number;
        return true;
    }

    int pop()
    {
        if (length)
            return array[length--];
        else
            cout << "Stack is empty!" << endl;
        return -1;
    }

    void print()
    {
        cout << "( ";
        for (int i = 0; i < length; i++)
            cout << array[i] << ' ';
        cout << ")"<< endl;
    }
};

int main()
{
    cout << "Task #1" << endl << endl;

    Power Number;
    Number.set (3.6, 5.4);
    Number.calculate();

    cout << endl << "Task #2" << endl;

    RGBA ColorDefault;
    ColorDefault.print();
    cout << endl;

    int red, green, blue, alpha;
    cout << "Please, enter value of red color: ";
    cin >> red;
    cout << "Please, enter value of green color: ";
    cin >> green;
    cout << "Please, enter value of blue color: ";
    cin >> blue;
    cout << "Please, enter value of alpha color: ";
    cin >> alpha;
    RGBA ColorUser (red, green, blue, alpha);
    ColorUser.print();

    cout << endl << "Task #3" << endl << endl;

    Stack stack;
     stack.reset();
     stack.print();
     stack.push(3);
     stack.push(7);
     stack.push(5);
     stack.print();
     stack.pop();
     stack.print();
     stack.pop();
     stack.pop();
     stack.print();

    return 0;
}
