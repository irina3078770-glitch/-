/* учет выполняемых банковских операций 
1.MAP,
2.SET, 
3.MULTIMAP,
4.MULTISET,
5.UNORDERED_MAP,  
6.UNORDERED_SET,  
7.UNORDERED_MULTIMAP,  
8.UNORDERED_MULTISET.

УМЕТЬ ОБОСНОВАТЬ ИСПОЛЬЗОВАНИЕ КАЖДОГО ТИПА КОНТЕЙНЕРА. 
В каждом индивидуальном задании необходимо создать вышеуказанные контейнеры, которые будут хранить объекты классов 
по предметной области, указанной в таблице ниже. Класс должен содержать функционал по предметной области 
(добавление, удаление, редактирование, поиск, фильтр данных). Для контейнера реализовать добавление, удаление, 
редактирование, вывод содержимого контейнера на экран и в файл, поиск и сортировку элементов. 
Необходимо создать удобное пользовательское меню для тестирования всех реализованных функций.  

*/
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <windows.h>

using namespace std;

inline void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

const int CLR_DEFAULT = 7;
const int CLR_RED = 12;
const int CLR_GREEN = 10;
const int CLR_YELLOW = 14;
const int CLR_CYAN = 11;
const int CLR_MAGENTA = 13;
const int CLR_BLUE = 9;

inline string toLowerStr(string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(static_cast<unsigned char>(str[i]));
    }
    return str;
}

//Банковская операция
class BankTransaction {
private:
    int id;
    string accountNumber; 
    string type; 
    double amount;
    double comission;

public:
    BankTransaction();
    BankTransaction(int id, string accNum, string type, double amount, double comission);

    int getId() const { return id; }
    string getAccountNumber() const { return accountNumber; }
    string getType() const { return type; }
    double getAmount() const { return amount; }
    double getCom() const { return comission; }

    void setId(int newId) { id = newId; }
    void setAccountNumber(const string& acc) { accountNumber = acc; }
    void setType(const string& t) { type = t; }
    void setAmount(double a) { amount = a; }
    void setFee(double c) { comission = c; }

    void inputData();

    bool operator<(const BankTransaction& other) const {
        return id < other.id;
    }
    bool operator==(const BankTransaction& other) const {
        return id == other.id;
    }

    friend ostream& operator<<(ostream& os, const BankTransaction& tx);
    friend istream& operator>>(istream& is, BankTransaction& tx);
};

//Менеджер контейнеров
class BankManager {
private:
    int nextId;

    map <int, BankTransaction> mapTx;                     // Справочник по ID: ID клиента - банковская операция
    set<string> setAccounts;                              // Уникальные счета клиентов
    multimap<string, BankTransaction> multimapAccTx;      // История по счёту: Банковский счёт - операции клиента
    multiset<double> multisetAmounts;                     // Сортированные операции по возрастанию  
    unordered_map<int, BankTransaction> unMapTx;          // Быстрый доступ по ID для поиска: ID клиента - банковская операция 
    unordered_set<string> unSetVerifiedAccs;              // Список счетов
    unordered_multimap<string, BankTransaction> unMultiMapTypeTx; // Группировка операций по типу: тип операции - сама операция
    unordered_multiset<double> unMultiSetCom;            // Комиссии банка

public:
    BankManager();

    void addTransaction(BankTransaction tx);
    bool removeTransaction(int id);
    bool editTransaction(int id);
    void searchById(int id) const;
    void filterByAmount(double minAmount) const;

    void printHeader() const;
    void displayAllMap() const;
    void displayAllSet() const;
    void displayAllMultiMap() const;
    void displayAllMultiSet() const;
    void displayAllUnorderedMap() const;
    void displayAllUnorderedSet() const;
    void displayAllUnorderedMultiMap() const;
    void displayAllUnorderedMultiSet() const;

    bool saveToFile(const string& filename) const;
    bool loadFromFile(const string& filename);

    static int inputInt(const string& prompt);
    static double inputDouble(const string& prompt);
    static string inputString(const string& prompt);
};



