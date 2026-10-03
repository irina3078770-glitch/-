/*Разработать набор классов (минимум 5 классов, связи между
классами: агрегация, композиция, наследование) по предметной области
«Магазин стройматериалов». Функционал программы должен позволить
собрать заказ. 
Необходимо реализовать в приложении следующие функции:
1. добавления данных в файл,
2. удаления данных из файла,
3. редактирования данных в файле,
4. просмотра данных файла,
5. поиска данных по необходимым параметрам в файле.
Обязательно использовать функции open(), is_open(), bad(), good(),
close(), eof(), fail(), seekg(), seekp(), tellg(), перегрузить операторы вывода в
поток << и считывания из потока >>.
*/
#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

int inputInt(const char* msg);
double inputDouble(const char* msg);
void inputString(char* buffer, int maxLen, const char* msg);

enum MaterialType {
	dryMix = 1, 
	paint=2
};

class Material {
public:
	int type;
	char name[50];
	double price;
	double weightKg;
	char color[30]; 
    int stock;
	int quantity;
};


class BuildingMaterial {
protected:
    char name[50];
    double price;
    int stock; 

public:
    BuildingMaterial(const char* n = "Неизвестно", double p = 0.0, int st = 0) : price(p), stock(st) {
        strcpy_s(name, n);
    }
    virtual ~BuildingMaterial() {}

    const char* getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    virtual MaterialType getType() const = 0;
    virtual void inputData();
    virtual void printData() const;

    virtual double getWeightKg() const { return 0.0; }
    virtual const char* getColor() const { return ""; }

    friend ostream& operator<<(ostream& os, const BuildingMaterial& mat);
    friend istream& operator>>(istream& is, BuildingMaterial& mat);
};

class DryMix : public BuildingMaterial {
private:
    double weightKg;
public:
    DryMix(const char* n = "Смесь", double p = 0.0, double w = 0.0, int st = 0)
        : BuildingMaterial(n, p, st), weightKg(w) {
    }

    double getWeightKg() const override { return weightKg; }
    MaterialType getType() const override { return dryMix; }
    void inputData() override;
    void printData() const override;
};

class Paint : public BuildingMaterial {
private:
    char color[30];
public:
    Paint(const char* n = "Краска", double p = 0.0, const char* c = "Прозрачный", int st = 0)
        : BuildingMaterial(n, p, st) {
        strcpy_s(color, c);
    }

    const char* getColor() const override { return color; }
    MaterialType getType() const override { return paint; }
    void inputData() override;
    void printData() const override;
};

class Catalog {
private:
    BuildingMaterial* items[5]; 
    int count;
public:
    Catalog() {
        items[0] = new DryMix("Штукатурка Knauf", 450.0, 30.0, 15);
        items[1] = new DryMix("Цемент М500", 380.0, 50.0, 40);
        items[2] = new DryMix("Шпатлевка Vetonit", 620.0, 25.0, 8);
        items[3] = new Paint("Краска Белая Tikkurila", 1200.0, "Белый", 5);
        items[4] = new Paint("Эмаль Серый ПФ-115", 350.0, "Серый", 20);
        count = 5;
    }

    ~Catalog() {
        for (int i = 0; i < count; i++) delete items[i];
    }

    void displayCatalog() const {
        cout << "\n================ ДОСТУПНЫЕ ТОВАРЫ В МАГАЗИНЕ ================\n";
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". " << *(items[i])
                << " | В наличии: " << items[i]->getStock() << " шт." << endl;
        }
        cout << "=============================================================\n";
    }

    int getCount() const { return count; }

    BuildingMaterial* getItem(int index) const {
        if (index >= 0 && index < count) return items[index];
        return nullptr;
    }

    BuildingMaterial* createCopy(int index) const {
        if (index < 0 || index >= count) return nullptr;

        BuildingMaterial* orig = items[index];
        if (orig->getType() == dryMix) {
            return new DryMix(orig->getName(), orig->getPrice(), orig->getWeightKg(), orig->getStock());
        }
        else {
            return new Paint(orig->getName(), orig->getPrice(), orig->getColor(), orig->getStock());
        }
    }
};

class OrderItem {
private:
    BuildingMaterial* material;
    int quantity;
public:
    OrderItem(BuildingMaterial* mat = nullptr, int qty = 0) : material(mat), quantity(qty) {}
    ~OrderItem() { 
        delete material; 
    }

    BuildingMaterial* getMaterial() const { return material; }
    int getQuantity() const { return quantity; }
    double getTotalCost() const { return material ? material->getPrice() * quantity : 0.0; }

    Material pack() const;
    void unpack(const Material& data);
};

class OrderManager {
private:
    char fileName[100];
    void checkStreamState(const ios& stream, const char* op) const;
public:
    OrderManager(const char* fName = "building_order.dat") { strcpy_s(fileName, fName); }

    void addRecord();
    void deleteRecord(int index);
    void editRecord(int index);
    void displayAll() const;
    void searchByName(const char* query) const;
    int getRecordCount() const;
};