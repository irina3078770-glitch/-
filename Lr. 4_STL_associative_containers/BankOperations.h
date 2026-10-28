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
    for (size_t i = 0; i < str.length(); i++) {
        str[i] = tolower(static_cast<unsigned char>(str[i]));
    }
    return str;
}

// 1. Базовый класс счета
class BankAccount {
protected:
    string accountNumber;
    string clientName;
public:
    BankAccount(string accNum = "BY00UNBS00000000000000000000", string name = "Неизвестно");
    virtual ~BankAccount() = default;

    string getAccountNumber() const { return accountNumber; }
    string getClientName() const { return clientName; }

    void setAccountNumber(const string& acc) { accountNumber = acc; }
    void setClientName(const string& name) { clientName = name; }

    virtual void printInfo() const;
};

// 2. Производный класс (Наследование)
class DepositAccount : public BankAccount {
private:
    double interestRate;
public:
    DepositAccount(string accNum = "BY00UNBS00000000000000000000", string name = "Неизвестно", double rate = 0.0);
    double getInterestRate() const { return interestRate; }
    void setInterestRate(double rate) { interestRate = rate; }
    void printInfo() const override;
};

// 3. Класс операции (Композиция)
class BankTransaction {
private:
    int id;
    double amount;
    string date;
    BankAccount account; // Композиция

public:
    BankTransaction();
    BankTransaction(int id, double amount, string date, BankAccount acc);

    int getId() const { return id; }
    double getAmount() const { return amount; }
    string getDate() const { return date; }
    BankAccount getAccount() const { return account; }

    void setId(int newId) { id = newId; }
    void setAmount(double amt) { amount = amt; }
    void setDate(const string& d) { date = d; }
    void setAccount(const BankAccount& acc) { account = acc; }

    void inputData();

    bool operator<(const BankTransaction& other) const { return id < other.id; }
    bool operator==(const BankTransaction& other) const { return id == other.id; }

    friend ostream& operator<<(ostream& os, const BankTransaction& tx);
    friend istream& operator>>(istream& is, BankTransaction& tx);
};

// 4. Класс филиала (Агрегация)
class BankBranch {
private:
    string branchName;
    const BankTransaction* lastTransaction;
public:
    BankBranch(string bName = "Центральное отделение (Минск)", const BankTransaction* trans = nullptr);
    void setLastTransaction(const BankTransaction* trans) { lastTransaction = trans; }
    void showBranchStatus() const;
};

// 5. Менеджер на базе 8 ассоциативных контейнеров
class BankManager {
private:
    int nextId;

    map<int, BankTransaction> mapTx;                          // Справочник по ID
    set<string> setAccounts;                                  // Уникальные IBAN счетов (по алфавиту)
    multimap<string, BankTransaction> multimapAccTx;          // История по счёту клиента
    multiset<double> multisetAmounts;                         // Суммы операций (по возрастанию)
    unordered_map<int, BankTransaction> unMapTx;              // Быстрый хеш-поиск по ID
    unordered_set<string> unSetVerifiedAccs;                  // Хеш-сет проверенных счетов
    unordered_multimap<string, BankTransaction> unMultiMapNameTx; // Группировка по ФИО клиента
    unordered_multiset<double> unMultiSetAmounts;             // Неупорядоченный мультисет сумм

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



