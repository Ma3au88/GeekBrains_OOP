/*
 * main.cpp
 * Homework #7
 * Created by Nikita Gusev
 */

#include <iostream>
#include <memory>

using namespace std;

/* Создайте класс Date с полями день, месяц, год и методами доступа к этим полям. Перегрузите оператор вывода для данного класса.
 * Создайте два "умных" указателя today и date. Первому присвойте значение сегодняшней даты.
 * Для него вызовите по отдельности методы доступа к полям класса Date, а также выведите на экран данные всего объекта
 * с помощью перегруженного оператора вывода. Затем переместите ресурс, которым владеет указатель today в указатель date.
 * Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль */

class Date {
    int day{};
    int month{};
    int year{};
public:
    Date() {}
    Date (int d, int m, int y) : day(d), month(m), year(y) {}
    ~Date() {}
    int getDay() const {
        return day;
    }
    int getMonth() const {
        return month;
    }
    int getYear() const {
        return year;
    }
    void setDay(int d) {
        day = d;
    }
    void setMonth(int m) {
        month = m;
    }
    void setYear(int y) {
        year = y;
    }
    friend void datecmp(shared_ptr<Date> d1, shared_ptr<Date> d2);
};

ostream& operator << (ostream& os, const Date& d) {
    return os << d.getDay() << '.' << d.getMonth() << '.' << d.getYear();
}

/* По условию предыдущей задачи создайте два умных указателя d1 и d2.
    - Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает их между собой
      (сравнение происходит по датам). Функция должна вернуть более позднюю дату.
    - Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в функцию в качестве параметров */

void datecmp(shared_ptr<Date> d1, shared_ptr<Date> d2) {
    if (d1->year > d2->year) {
        cout << "Later date: " << *d1 << endl;
    }
    if (d1->year == d2->year && d1->month > d2->month) {
        cout << "Later date: " << *d1 << endl;
    }
    if (d1->year == d2->year && d1->month == d2->month && d1->day > d2->day) {
        cout << "Later date: " << *d1 << endl;
    }

    if (d2->year > d1->year) {
        cout << "Later date: " << *d2 << endl;
    }
    if (d2->year == d1->year && d2->month > d1->month) {
        cout << "Later date: " << *d2 << endl;
    }
    if (d2->year == d1->year && d2->month == d1->month && d2->day > d1->day) {
        cout << "Later date: " << *d2 << endl;
    }
}

int main()
{
    cout << "Task #1" << endl;

    unique_ptr<Date> today = make_unique<Date>();
    today->setDay(22);
    today->setMonth(07);
    today->setYear(2021);
    cout << "Today: " << *today << endl;
    unique_ptr<Date> date = move(today);

    if (today) {
        cout << "Today is not null" << endl;
    } else {
        cout << "Today is null" << endl;
    }

    if (date) {
        cout << "Date is not null" << endl;
    } else {
        cout << "Date is null" << endl;
    }

    cout << "Date: " << *date << endl;

    cout << endl << "Task #2" << endl;

    auto date1 = make_shared<Date> (12, 6, 2020);
    auto date2 = make_shared<Date> (02, 9, 2021);
    cout << *date1 << endl;
    cout << *date2 << endl;
    datecmp(date1, date2);
    cout << endl;

    auto date3 = make_shared<Date> (05, 6, 2020);
    auto date4 = make_shared<Date> (15, 9, 2021);
    cout << *date3 << endl;
    cout << *date4 << endl;
    cout << "Swap: " << endl;
    date3.swap(date4);
    cout << *date3 << endl;
    cout << *date4 << endl;

    return 0;
}
