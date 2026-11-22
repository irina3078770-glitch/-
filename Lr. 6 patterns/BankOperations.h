/*1.	«фабричный метод»,
2.	«фабричный метод с аргументами»,
3.	«фабричный конструктор»,
4.	«полиморфная фабрика»,
5.	 «полиморфное копирование».
Для всех типов необходимо реализовать возможность добавления, удаления, редактирования, вывода содержимого объектов на экран и в файл.
*/

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>
#include <windows.h>

using namespace std;

// Перечисление типов операций для паттерна "Фабричный метод с аргументами"
enum OperationType {
    OP_DEPOSIT = 1, // пополнение
    OP_WITHDRAWAL = 2, // снятие наличных
    OP_TRANSFER = 3, //перевод
    OP_UTILITY = 4, // оплата услуг
    OP_EXCHANGE = 5 // обмен валют
};

void setColor(int color);

int inputInt(const char* msg);
double inputDouble(const char* msg);
string inputString(const char* msg);
string inputAlphanumericString(const char* msg);
string inputDateString(const char* msg);

int generateUniqueOperationId(const vector<unique_ptr<class BankOperation> >& ops);

// Иерархия документов для паттерна "Полиморфная фабрика"
class OperationDocument {
public:
    virtual ~OperationDocument() {}
    virtual void printDocument(ostream& os) const = 0;
    virtual string getDocumentTitle() const = 0;
};

class DepositReceipt : public OperationDocument {
private:
    int operationId;
    string date;
    double amount;
    string accountNumber;
    string source;
public:
    DepositReceipt(int id, const string& d, double amt, const string& acc, const string& src);
    void printDocument(ostream& os) const override;
    string getDocumentTitle() const override;
};

class WithdrawalSlip : public OperationDocument {
private:
    int operationId;
    string date;
    double amount;
    string accountNumber;
    string atmId;
public:
    WithdrawalSlip(int id, const string& d, double amt, const string& acc, const string& atm);
    void printDocument(ostream& os) const override;
    string getDocumentTitle() const override;
};

class TransferInvoice : public OperationDocument {
private:
    int operationId;
    string date;
    double amount;
    string accountNumber;
    string targetAccount;
public:
    TransferInvoice(int id, const string& d, double amt, const string& acc, const string& tgt);
    void printDocument(ostream& os) const override;
    string getDocumentTitle() const override;
};

class PaymentCheck : public OperationDocument {
private:
    int operationId;
    string date;
    double amount;
    string accountNumber;
    string serviceProvider;
public:
    PaymentCheck(int id, const string& d, double amt, const string& acc, const string& prov);
    void printDocument(ostream& os) const override;
    string getDocumentTitle() const override;
};

class ExchangeCertificate : public OperationDocument {
private:
    int operationId;
    string date;
    double amount;
    string accountNumber;
    string targetCurrency;
    double exchangeRate;
public:
    ExchangeCertificate(int id, const string& d, double amt, const string& acc, const string& curr, double rate);
    void printDocument(ostream& os) const override;
    string getDocumentTitle() const override;
};

// Иерархия параметров для паттерна "Фабричный метод с аргументами"
class OperationSpec {
public:
    int id;
    string date;
    double amount;
    string accountNumber;

    OperationSpec(int opId, const string& opDate, double opAmount, const string& opAccount);
    virtual ~OperationSpec() {}
    virtual OperationType getType() const = 0;
};

class DepositSpec : public OperationSpec {
public:
    string source;
    DepositSpec(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opSource);
    OperationType getType() const override;
};

class WithdrawalSpec : public OperationSpec {
public:
    string atmId;
    WithdrawalSpec(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opAtm);
    OperationType getType() const override;
};

class TransferSpec : public OperationSpec {
public:
    string targetAccount;
    TransferSpec(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opTarget);
    OperationType getType() const override;
};

class UtilityPaymentSpec : public OperationSpec {
public:
    string serviceProvider;
    UtilityPaymentSpec(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opProvider);
    OperationType getType() const override;
};

class CurrencyExchangeSpec : public OperationSpec {
public:
    string targetCurrency;
    double exchangeRate;
    CurrencyExchangeSpec(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opCurrency, double opRate);
    OperationType getType() const override;
};

// Базовый класс банковской операции
class BankOperation {
protected:
    int id;
    string date;
    double amount;
    string accountNumber;

    bool readCommonFields(istream& is);

public:
    // Тип указателя на функцию для паттерна "Фабричный конструктор"
    typedef unique_ptr<BankOperation>(*OperationFactoryFunc)();
    static vector<pair<int, OperationFactoryFunc> > operationRegistry;

    BankOperation();
    BankOperation(int opId, const string& opDate, double opAmount, const string& opAccount);
    virtual ~BankOperation() {}

    int getId() const;
    void setId(int newId);
    string getDate() const;
    double getAmount() const;
    string getAccountNumber() const;

    virtual OperationType getOperationType() const = 0;
    virtual string getTypeName() const = 0;
    virtual void inputFields(int newId) = 0;
    virtual void edit() = 0;
    virtual void printDetails(ostream& os) const = 0;
    virtual void writeRecord(ostream& os) const = 0;
    virtual bool readFromStream(istream& is) = 0;

    friend ostream& operator<<(ostream& os, const BankOperation& op);
    friend istream& operator>>(istream& is, BankOperation& op);

    // ПАТТЕРН 2: ФАБРИЧНЫЙ МЕТОД С АРГУМЕНТАМИ
    static unique_ptr<BankOperation> createWithArgs(const OperationSpec* spec);

    // ПАТТЕРН 3: ФАБРИЧНЫЙ КОНСТРУКТОР - динамический реестр типов
    static void registerCreator(OperationFactoryFunc creatorFunc);
    static unique_ptr<BankOperation> createFromRegistry(int registryIndex, int newId);
    static size_t getRegistrySize();

    // ПАТТЕРН 4: ПОЛИМОРФНАЯ ФАБРИКА
    virtual unique_ptr<OperationDocument> createDocument() const = 0;

    // ПАТТЕРН 5: ПОЛИМОРФНОЕ КОПИРОВАНИЕ
    virtual unique_ptr<BankOperation> clone() const = 0;
};

// ПАТТЕРН 1: ФАБРИЧНЫЙ МЕТОД 
class OperationCreator {
public:
    virtual ~OperationCreator() {}
    virtual unique_ptr<BankOperation> createOperation() const = 0;
};

class DepositCreator : public OperationCreator {
public:
    unique_ptr<BankOperation> createOperation() const override;
};

class WithdrawalCreator : public OperationCreator {
public:
    unique_ptr<BankOperation> createOperation() const override;
};

class TransferCreator : public OperationCreator {
public:
    unique_ptr<BankOperation> createOperation() const override;
};

class UtilityPaymentCreator : public OperationCreator {
public:
    unique_ptr<BankOperation> createOperation() const override;
};

class CurrencyExchangeCreator : public OperationCreator {
public:
    unique_ptr<BankOperation> createOperation() const override;
};

// ПАТТЕРН 5: ПОЛИМОРФНОЕ КОПИРОВАНИЕ
template <typename DerivedT>
class ClonableOperation : public BankOperation {
public:
    ClonableOperation() : BankOperation() {}
    ClonableOperation(int opId, const string& opDate, double opAmount, const string& opAccount)
        : BankOperation(opId, opDate, opAmount, opAccount) {
    }

    // ПАТТЕРН 5: ПОЛИМОРФНОЕ КОПИРОВАНИЕ
    unique_ptr<BankOperation> clone() const override;
};

// 5 производных классов банковских операций

// Пополнение счета
class DepositOperation : public ClonableOperation<DepositOperation> {
private:
    string source;
public:
    DepositOperation();
    DepositOperation(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opSource);

    OperationType getOperationType() const override;
    string getTypeName() const override;
    void inputFields(int newId) override;
    void edit() override;
    void printDetails(ostream& os) const override;
    void writeRecord(ostream& os) const override;
    bool readFromStream(istream& is) override;

    // ПАТТЕРН 3: ФАБРИЧНЫЙ КОНСТРУКТОР - метод создания экземпляра конкретным классом
    static unique_ptr<BankOperation> createInstance();
    static void Register();

    // ПАТТЕРН 4: ПОЛИМОРФНАЯ ФАБРИКА
    unique_ptr<OperationDocument> createDocument() const override;
};

// Снятие наличных
class WithdrawalOperation : public ClonableOperation<WithdrawalOperation> {
private:
    string atmId;
public:
    WithdrawalOperation();
    WithdrawalOperation(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opAtm);

    OperationType getOperationType() const override;
    string getTypeName() const override;
    void inputFields(int newId) override;
    void edit() override;
    void printDetails(ostream& os) const override;
    void writeRecord(ostream& os) const override;
    bool readFromStream(istream& is) override;

    // ПАТТЕРН 3: ФАБРИЧНЫЙ КОНСТРУКТОР
    static unique_ptr<BankOperation> createInstance();
    static void Register();

    // ПАТТЕРН 4: ПОЛИМОРФНАЯ ФАБРИКА
    unique_ptr<OperationDocument> createDocument() const override;
};

// Перевод
class TransferOperation : public ClonableOperation<TransferOperation> {
private:
    string targetAccount;
public:
    TransferOperation();
    TransferOperation(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opTarget);

    OperationType getOperationType() const override;
    string getTypeName() const override;
    void inputFields(int newId) override;
    void edit() override;
    void printDetails(ostream& os) const override;
    void writeRecord(ostream& os) const override;
    bool readFromStream(istream& is) override;

    // ПАТТЕРН 3: ФАБРИЧНЫЙ КОНСТРУКТОР
    static unique_ptr<BankOperation> createInstance();
    static void Register();

    // ПАТТЕРН 4: ПОЛИМОРФНАЯ ФАБРИКА
    unique_ptr<OperationDocument> createDocument() const override;
};

// Оплата услуг
class UtilityPaymentOperation : public ClonableOperation<UtilityPaymentOperation> {
private:
    string serviceProvider;
public:
    UtilityPaymentOperation();
    UtilityPaymentOperation(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opProvider);

    OperationType getOperationType() const override;
    string getTypeName() const override;
    void inputFields(int newId) override;
    void edit() override;
    void printDetails(ostream& os) const override;
    void writeRecord(ostream& os) const override;
    bool readFromStream(istream& is) override;

    // ПАТТЕРН 3: ФАБРИЧНЫЙ КОНСТРУКТОР
    static unique_ptr<BankOperation> createInstance();
    static void Register();

    // ПАТТЕРН 4: ПОЛИМОРФНАЯ ФАБРИКА
    unique_ptr<OperationDocument> createDocument() const override;
};

// Обмен валют
class CurrencyExchangeOperation : public ClonableOperation<CurrencyExchangeOperation> {
private:
    string targetCurrency;
    double exchangeRate;
public:
    CurrencyExchangeOperation();
    CurrencyExchangeOperation(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opCurrency, double opRate);

    OperationType getOperationType() const override;
    string getTypeName() const override;
    void inputFields(int newId) override;
    void edit() override;
    void printDetails(ostream& os) const override;
    void writeRecord(ostream& os) const override;
    bool readFromStream(istream& is) override;

    // ПАТТЕРН 3: ФАБРИЧНЫЙ КОНСТРУКТОР
    static unique_ptr<BankOperation> createInstance();
    static void Register();

    // ПАТТЕРН 4: ПОЛИМОРФНАЯ ФАБРИКА
    unique_ptr<OperationDocument> createDocument() const override;
};

// ПАТТЕРН 5: ПОЛИМОРФНОЕ КОПИРОВАНИЕ (определение после объявления всех производных классов)
template <typename DerivedT>
unique_ptr<BankOperation> ClonableOperation<DerivedT>::clone() const {
    return unique_ptr<BankOperation>(new DerivedT(static_cast<const DerivedT&>(*this)));
}

void addOperationMenu(vector<unique_ptr<BankOperation> >& ops);
void deleteOperationById(vector<unique_ptr<BankOperation> >& ops);
void editOperationById(vector<unique_ptr<BankOperation> >& ops);
void displayAllOperations(const vector<unique_ptr<BankOperation> >& ops);
void saveOperationsToFile(const vector<unique_ptr<BankOperation> >& ops, const string& filename);
void loadOperationsFromFile(vector<unique_ptr<BankOperation> >& ops, const string& filename);