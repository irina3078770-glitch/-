#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <windows.h>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

void setColor(int color);
int inputInt(const char* msg);
double inputDouble(const char* msg);
string inputString(const char* msg);
string inputAlphanumericString(const char* msg);
string inputDateString(const char* msg);

int generateUniqueIdForQueue(const queue<class BankTransaction>& q);
int generateUniqueIdForStack(const stack<class BankTransaction>& s);
int generateUniqueIdForPriorityQueue(const priority_queue<class CreditApplication>& pq);

class Transaction {
protected:
    int id;
    double amount;
    string date;
public:
    Transaction(int id, double amount, string date) : id(id), amount(amount), date(date) {}
    virtual ~Transaction() {}

    int getId() const { return id; }
    double getAmount() const { return amount; }
    string getDate() const { return date; }
    void setAmount(double amt) { amount = amt; }
};

class BankTransaction : public Transaction {
protected:
    string accountNumber;
    string clientName;
public:
    BankTransaction(int id, double amount, string date, string accNum, string name)
        : Transaction(id, amount, date), accountNumber(accNum), clientName(name) {
    }

    string getAccountNumber() const { return accountNumber; }
    string getClientName() const { return clientName; }
    void setClientName(const string& name) { clientName = name; }

    friend ostream& operator<<(ostream& out, const BankTransaction& tx) {
        out << "ID: " << setw(6) << left << tx.id
            << "Сумма: " << setw(10) << right << tx.amount << " BYN"
            << " | Дата: " << setw(10) << tx.date
            << " | Счет: " << setw(15) << tx.accountNumber
            << " | Клиент: " << tx.clientName;
        return out;
    }

    friend istream& operator>>(istream& in, BankTransaction& tx) {
        if (in >> tx.id >> tx.amount >> tx.date >> tx.accountNumber) {
            in.ignore();
            getline(in, tx.clientName); 
        }
        return in;
    }
};

class CreditApplication : public BankTransaction {
private:
    int creditScore;
public:
    CreditApplication(int id, double amount, string date, string accNum, string name, int score)
        : BankTransaction(id, amount, date, accNum, name), creditScore(score) {
    }

    int getCreditScore() const { return creditScore; }
    void setCreditScore(int score) { creditScore = score; }

    bool operator<(const CreditApplication& other) const {
        return this->creditScore < other.creditScore;
    }

    friend ostream& operator<<(ostream& out, const CreditApplication& app) {
        out << "ID: " << setw(6) << left << app.getId()
            << " | Сумма: " << setw(10) << right << app.getAmount() << " BYN"
            << " | Дата: " << setw(10) << app.getDate()
            << " | Счет: " << setw(15) << app.getAccountNumber()
            << " | Клиент: " << setw(15) << left << app.getClientName()
            << " | Рейтинг: " << setw(3) << right << app.creditScore << "/100";
        return out;
    }

    friend istream& operator>>(istream& in, CreditApplication& app) {
        if (in >> app.id >> app.amount >> app.date >> app.accountNumber >> app.creditScore) {
            in.ignore(); 
            getline(in, app.clientName);
        }
        return in;
    }
};

void QueueMenu();
void StackMenu();
void PriorityQueueMenu();

void saveQueueToFile(const queue<class BankTransaction>& q, const string& filename);
void loadQueueFromFile(queue<class BankTransaction>& q, const string& filename);

void saveStackToFile(const stack<class BankTransaction>& s, const string& filename);
void loadStackFromFile(stack<class BankTransaction>& s, const string& filename);

void savePriorityQueueToFile(const priority_queue<class CreditApplication>& pq, const string& filename);
void loadPriorityQueueFromFile(priority_queue<class CreditApplication>& pq, const string& filename);

void editQueueAmount(queue<BankTransaction>& q);
void filterQueueByAmount(const queue<BankTransaction>& q);

void editStackAmount(stack<BankTransaction>& s);
void filterStackByAmount(const stack<BankTransaction>& s);

void editPriorityQueueAmount(priority_queue<CreditApplication>& pq);
void filterPriorityQueueByAmount(const priority_queue<CreditApplication>& pq);