/*
 * main.cpp
 * Homework #2
 * Created by Nikita Gusev
 */

#include <iostream>

using namespace std;

/* Создать класс Person (человек) с полями: имя, возраст, пол и вес.
 * Определить методы переназначения имени, изменения возраста и веса.
 * Создать производный класс Student (студент), имеющий поле года обучения.
 * Определить методы переназначения и увеличения этого значения.
 * Создать счетчик количества созданных студентов. В функции main() создать несколько студентов.
 * По запросу вывести определенного человека */

enum Gender
{
    GENDER_MALE,
    GENDER_FEMALE
};

class Person
{
    string name;
    int age;
    Gender gender;
    float weight;
public:
    Person(string n, int a, Gender g, float w) :
    name(n), age(a), gender(g), weight(w) {}

    void setName(string n = "")
    {
        if (n == "")
        {
            cout << "Enter name: ";
            cin >> name;
        }
        else
            name = n;
    }

    void setAge(int a = 0)
    {
        if (a == 0)
        {
            cout << "Enter age: ";
            cin >> age;
        }
        else
            age = a;
    }

    void setWeight(float w = 0.0)
    {
        if (w == 0)
        {
            cout << "Enter weight: ";
            cin >> weight;
        }
        else
            weight = w;
    }

    void print() const
    {
        cout << "Name: " << name << "\n"
             << "Age: " << age << "\n"
             << "Gender: " << (gender == GENDER_MALE ? "Male" : "Female") << "\n"
             << "Weight: " << weight << endl;
    }
};

class Student : public Person
{
    static int count;
    int year;
public:
    Student(string name, int age, Gender gender, float weight, int y) :
        Person(name, age, gender, weight), year(y)
    {
        count++;
    }

    static void printCount()
    {
        cout << "Number of students: " << count << endl;
    }

    void setYearOfStudy(int y = 0)
    {
        if (y == 0)
        {
            cout << "Enter the year of study: ";
            cin >> y;
        }
        else
            y = year;
    }

    void Year()
    {
        year++;
    }

    void print() const
    {
        Person::print();
        cout << "Year of study: " << year << endl;
    }

    ~Student()
    {
        count--;
    }
};

int Student::count = 0;

/* Создать классы Apple (яблоко) и Banana (банан), которые наследуют класс Fruit (фрукт).
 * У Fruit есть две переменные-члена: name (имя) и color (цвет).
 * Добавить новый класс GrannySmith, который наследует класс Apple */

class Fruit
{
    string name;
    string color;
public:
    void setName(string n)
    {
        name = n;
    }

    void setColor(string c)
    {
        color = c;
    }

    const string& getName()
    {
        return name;
    }

    const string& getColor()
    {
        return color;
    }
};

class Apple : public Fruit
{
public:
    Apple(string c = "green")
    {
        setName("apple");
        setColor(c);
    }
};

class Banana : public Fruit
{
public:
    Banana(string c = "yellow")
    {
        setName("banana");
        setColor(c);
    }
};

class GrannySmith : public Apple
{
public:
    GrannySmith()
    {
        setName("Granny Smith " + Apple::getName());
    }
};

int main()
{
    cout << "Task #1" << endl << endl;

    Student nik("Nikita", 33, GENDER_MALE, 70.8, 2010);
    nik.print();
    cout << endl;
    Student nastya("Anastasia", 30, GENDER_FEMALE, 63.3, 2013);
    nastya.print();
    cout << endl;
    Student::printCount();

    cout << endl << "Task #2" << endl << endl;

    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    return 0;
}
