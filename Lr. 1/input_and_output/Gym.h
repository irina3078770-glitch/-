/*Разработать набор классов (минимум 5 классов, связи между
классами: агрегация, композиция, наследование) по предметной области
«Тренажерный зал». Функционал программы должен позволить собрать
данные о необходимых тренажерах.
В каждом индивидуальном задании необходимо реализовать функции
1. просмотра,
2. добавления,
3. удаления,
4. редактирования,
5. сортировки,
6. поиска данных по необходимым параметрам (с учетом
индивидуального задания).
*/

#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<limits>
#define NOMINMAX
#include<windows.h>


using namespace std;

class Address {
private:
    string city, street;
    int building;
public:
    Address();
    Address(const string& c, const string& s, int b);

    string getCity() const;
    string getStreet() const;
    int getBuilding() const;
};

class Manufacturer {
private:
    string name, country;
public:
    Manufacturer();
    Manufacturer(const string& n, const string& c);

    string getName() const;
    string getCountry() const;
};

class Equipment {
protected:
    int id;
    string name;
    Manufacturer manufacturer;
public:
    Equipment();
    Equipment(int id, const string& n, const Manufacturer& m);
    virtual ~Equipment() {}

    int getId() const;
    string getName() const;
    Manufacturer getManufacturer() const;

    void setName(const string& n);

    virtual string getType() const = 0;
    virtual int getParam1() const = 0;
    virtual int getParam2() const = 0;
};

class Treadmill : public Equipment {
private:
    int maxSpeed, maxIncline;
public:
    Treadmill();
    Treadmill(int id, const string& n, const Manufacturer& m, int speed, int incline);

    int getMaxSpeed() const;
    int getMaxIncline() const;

    string getType() const override;
    int getParam1() const override { return maxSpeed; }
    int getParam2() const override { return maxIncline; }
};

class Bike : public Equipment {
private:
    int maxLoad, programs;
public:
    Bike();
    Bike(int id, const string& n, const Manufacturer& m, int load, int prog);

    int getMaxLoad() const;
    int getPrograms() const;

    string getType() const override;
    int getParam1() const override { return maxLoad; }
    int getParam2() const override { return programs; }
};

class Gym {
private:
    string gymName;
    Address address; //композиция
    int lastId = 0;

    Equipment** a;
    int size, capacity;

    void resize();

public:
    Gym(const string& name, const Address& addr);
    ~Gym();

    void addEquipment(Equipment* e);
    void deleteEquipment(int id);
    void editEquipment(int id);
    void updateLastId();
    void sortById();
    void searchByName(const string& part);
    void viewAll() const;

    void saveToFile(const string& filename) const;
    void loadDemo(const string& filename);

    int generateId() { return ++lastId; }
    int findIndexById(int id) const;
    int getSize() const { return size; }
    Equipment* getAt(int i) const { return a[i]; }
};

int inputInt(const char* msg);
double inputDouble(const char* msg);
string inputString(const char* msg);

void printTable(const Gym& gym, ostream& os);

