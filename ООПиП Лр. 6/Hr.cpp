/*Построить иерархию классов согласно схеме наследования,
приведенной на рисунке ниже по предметной области «HR-менеджмент».
Каждый класс должен содержать необходимые конструкторы и методы
работы с полями классов. Функция main() должна иллюстрировать работу с
массивами объектов всех созданных классов. При необходимости атрибуты
доступа при наследовании можно изменять. При необходимости
самостоятельно добавить классы для реализации множественного
наследования.
*/

#include<iostream>
#include<fstream>
#include "Hr.h"

using namespace std;

Employee::Employee(const char* n, int a, double s) : age(a), salary(s)
{
    strcpy_s(name, 50, n);
}

void Employee::print() const {
    cout << "Имя: " << name << endl;
    cout << "Возраст: " << age << endl;
    cout << "Зарплата: " << salary << endl;
}

void Employee::save(ofstream& out) const {
    out << name << ";" << age << ";" << salary;
}

//временный сотрудник
TemporaryEmployee::TemporaryEmployee(const char* n, int a, double s,
    int days) : Employee(n, a, s), contractDays(days) {
}

void TemporaryEmployee::print() const {
    Employee::print();
    cout << " временный сотрудник" << ", контракт (дней): " << contractDays;
}

void TemporaryEmployee::save(ofstream& out) const {
    Employee::save(out);
    out << ";TEMP;" << contractDays;
}

PermanentEmployee::PermanentEmployee(const char* n, int a, double s,
    int exp) : Employee(n, a, s), experienceYears(exp) {
}

void PermanentEmployee::print() const {
    Employee::print();
    cout << " постоянный сотрудник" << ", стаж (лет): " << experienceYears;
}

void PermanentEmployee::save(ofstream& out) const {
    Employee::save(out);
    out << ";PERM;" << experienceYears;
}


Consultant::Consultant(const char* n, int a, double s,
    int days, const char* proj) : Employee(n, a, s),
    TemporaryEmployee(n, a, s, days)
{
    strcpy_s(project, 50, proj);
}

void Consultant::print() const {
    TemporaryEmployee::print();
    cout << " консультант"
    << ", проект: " << project;
}

void Consultant::save(ofstream& out) const {
    TemporaryEmployee::save(out);
    out << ";CONS;" << project;
}


Manager::Manager(const char* n, int a, double s, int team) : Employee(n, a, s), teamSize(team) {
}

void Manager::print() const {
    Employee::print();
    cout << " менеджер" << ", команда: " << teamSize;
}

void Manager::save(ofstream& out) const {
    Employee::save(out);
    out << ";MAN;" << teamSize;
}


ConsultantManager::ConsultantManager(const char* n, int a, double s, int days, const char* proj, int team)
    : Employee(n, a, s),
    Consultant(n, a, s, days, proj),
    Manager(n, a, s, team) {
}

void ConsultantManager::print() const {
    cout << "Консультант-менеджер ";
    Employee::print();
    cout << " контракт: " << contractDays
    << ", проект: " << project
    << ", команда: " << teamSize;
}

void ConsultantManager::save(ofstream& out) const {
    Employee::save(out);
    out << ";CONS-MAN;"
    << contractDays << ";"
    << project << ";"
    << teamSize;
}


PermanentManager::PermanentManager(const char* n, int a, double s, int exp, int team) : Employee(n, a, s),
    PermanentEmployee(n, a, s, exp),
    Manager(n, a, s, team) {
}

void PermanentManager::print() const {
    cout << "Постоянный менеджер ";
    Employee::print();
    cout << " стаж: " << experienceYears << ", команда: " << teamSize;
}

void PermanentManager::save(ofstream& out) const {
    Employee::save(out);
    out << ";PERM-MAN;"
    << experienceYears << ";"
    << teamSize;
}

Director::Director(const char* n, int a, double s,
    int team, int lvl) : Employee(n, a, s),
    Manager(n, a, s, team),
    level(lvl)
{
}

void Director::print() const {
    cout << "Директор ";
    Employee::print();
    cout << " команда: " << teamSize
    << " стаж: " << level;
}

void Director::save(ofstream& out) const {
    Employee::save(out);
    out << ";DIR;"
    << teamSize << ";"
    << level;
}
