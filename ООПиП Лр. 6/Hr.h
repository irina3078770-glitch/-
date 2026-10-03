/*Построить иерархию классов согласно схеме наследования,
приведенной на рисунке ниже по предметной области «HR-менеджмент».
Каждый класс должен содержать необходимые конструкторы и методы
работы с полями классов. Функция main() должна иллюстрировать работу с
массивами объектов всех созданных классов. При необходимости атрибуты
доступа при наследовании можно изменять. При необходимости
самостоятельно добавить классы для реализации множественного
наследования.
*/
#pragma once
#include <iostream>
#include <cstring>

using namespace std;

//базовый класс
class Employee {
protected:
    char name[50];
    int age;
    double salary;
public:
    Employee(const char* n = "", int a = 0, double s = 0.0);
    virtual ~Employee() {}

    virtual void print() const;
    virtual void save(ofstream& out) const;
};

//временный сотрудник
class TemporaryEmployee : public virtual Employee {
protected:
    int contractDays;
public:
    TemporaryEmployee(const char* n = "", int a = 0, double s = 0.0,
        int days = 0);

    void print() const override; //метод переопределяет виртуальный метод базового класса
    void save(ofstream& out) const override;
};

//постоянный сотрудник
class PermanentEmployee : public virtual Employee {
protected:
    int experienceYears;
public:
    PermanentEmployee(const char* n = "", int a = 0, double s = 0.0,
        int exp = 0);

    void print() const override;
    void save(ofstream& out) const override;
};

//консультант
class Consultant : public TemporaryEmployee {
protected:
    char project[50];
public:
    Consultant(const char* n = "", int a = 0, double s = 0.0,
        int days = 0, const char* proj = "");

    void print() const override;
    void save(ofstream& out) const override;
};

class Manager : public virtual Employee {
protected:
    int teamSize;
public:
    Manager(const char* n = "", int a = 0, double s = 0.0,
        int team = 0);

    void print() const override;
    void save(ofstream& out) const override;
};

class ConsultantManager : public Consultant, public Manager {
public:
    ConsultantManager(const char* n = "", int a = 0, double s = 0.0,
        int days = 0, const char* proj = "",
        int team = 0);

    void print() const override;
    void save(ofstream& out) const override;
};

//постоянный менеджер
class PermanentManager : public PermanentEmployee, public Manager {
public:
    PermanentManager(const char* n = "", int a = 0, double s = 0.0,
        int exp = 0, int team = 0);

    void print() const override;
    void save(ofstream& out) const override;
};

class Director : public Manager {
protected:
    int level;
public:
    Director(const char* n = "", int a = 0, double s = 0.0,
        int team = 0, int lvl = 0);

    void print() const override;
    void save(ofstream& out) const override;
};

