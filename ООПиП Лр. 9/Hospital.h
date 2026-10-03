/*. Разработать набор классов (минимум 5 классов, связи между
классами: агрегация, композиция, наследование) по предметной области
«Медицинское учреждение». Функционал программы должен позволить
собрать персонал для обслуживания отделения. Сгенерировать минимум
пять типов исключительных ситуаций. Реализовать перенаправление
исключительных ситуаций. Сгенерировать минимум одну исключительную
ситуацию с оператором new. Создать исключительную ситуацию в
конструкторе и продемонстрировать вызов конструкторов и деструкторов.
Задать собственную функцию завершения. Создать собственный
(пользовательский) класс исключения, сгенерировать исключение этого типа
и обработать его. 
*/
#pragma once
#include<iostream>
#include<limits>
#include<ctype.h>
#include<new>
#include<exception>

using namespace std;

int inputInt(const char* msg);
double inputDouble(const char* msg);
void inputString(char* buffer, int maxLen, const char* msg);

class StaffException {
	const char* msg;
public: 
	StaffException(const char* m);
	const char* what() const;
};

class Staff {
protected:
    char name[50];
    int age;
public:
    Staff();
    virtual ~Staff();
    virtual void input();
    virtual void print() const;
};

class Doctor : public Staff {
    int exp;
public:
    Doctor();
    ~Doctor();
    void input();
    void print() const;
};

class Nurse : public Staff {
    int shift;
public:
    Nurse();
    ~Nurse();
    void input();
    void print() const;
};

class Technician : public Staff {
    double salary;
public:
    Technician();
    ~Technician();
    void input();
    void print() const;
};

//композиция
class Ward {
    int number;
    int beds;
public:
    Ward();
    ~Ward();
    void input();
    void print() const;
};

class Department {
    char name[50];
    Ward ward; //композиция
    Staff* staff[10]; //агрегация
    int count;
public:
    Department();
    ~Department();
    void input();
    void add(Staff* s);
    void print() const;
};

//композиция
class Hospital {
    char name[50];
    Department dept;
    Staff* all[20];
    int total;
public:
    Hospital();
    ~Hospital();
    void input();
    void addDoctor();
    void addNurse();
    void addTech();
    void print() const;
};

void myTerminate();