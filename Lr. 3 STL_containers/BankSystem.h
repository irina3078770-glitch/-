/*9. Разработать набор классов (минимум 5 классов, связи между классами: агрегация, композиция, наследование) 
по предметной области «Учет выполняемых банковских операций». Функционал программы должен позволить вести учет 
данных по предметной области. Использовать контейнеры list, vector, array, которые будут хранить объекты созданных классов. 
Реализовать функционал по предметной области (просмотр, добавление, удаление, редактирование, поиск, фильтр данных). 
Сформировать табличный вывод всех данных на экран и в файл. Для каждого контейнера реализовать добавление, удаление, 
редактирование, вывод содержимого контейнера на экран и в файл, поиск и сортировку элементов. 
Cоздать удобное пользовательское меню для тестирования всех реализованных функций. 
Уметь обосновать использование каждого типа контейнера. 
*/
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <array>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cctype>
#include <sstream>
#include <windows.h>

using namespace std;

void setColor(int color);
void clearScreen();

int inputInt(const char* msg);
double inputDouble(const char* msg);
void inputString(char* buffer, int maxLen, const char* msg);
string inputAlphanumericString(const char* msg);
string inputDateString(const char* msg);

// Банковский счёт
class BankAccount {
protected:
    string accountNumber; 
    string clientName;   
public:
    BankAccount(string accNum = "BY00UNBS00000000000000000000", string name = "Неизвестно");
    virtual ~BankAccount() = default;

    string getAccountNumber() const;
    string getClientName() const;

    void setAccountNumber(const string& acc);
    void setClientName(const string& name);

    virtual void printInfo() const;
};

// Депозитный счёт
class DepositAccount : public BankAccount {
private:
    double interestRate; // Процентная ставка
public:
    DepositAccount(string accNum = "BY00UNBS00000000000000000000", string name = "Неизвестно", double rate = 0.0);

    double getInterestRate() const;
    void setInterestRate(double rate);

    void printInfo() const override;
};

// Банковская операция (композиция)
class BankTransaction {
private:
    static int nextId;
    int id; 
    double amount; // Сумма в BYN
    string date;
    BankAccount account; 

public:
    BankTransaction(double amt = 0.0, string d = "01.01.2026", BankAccount acc = BankAccount());

    BankTransaction(int tId, double amt, string d, BankAccount acc);

    int getId() const;
    double getAmount() const;
    string getDate() const;
    BankAccount getAccount() const;

    void setId(int newId);
    void setAmount(double amt);
    void setDate(const string& d);
    void setAccount(const BankAccount& acc);

    static void setNextId(int newNextId);
    static int getNextId();

    void printRow() const;

   
    bool operator<(const BankTransaction& other) const;
    bool operator>(const BankTransaction& other) const;
    bool operator==(const BankTransaction& other) const;

    friend ostream& operator<<(ostream& os, const BankTransaction& t);
    friend istream& operator>>(istream& is, BankTransaction& t);
};

// Банковский филиал (агрегация)
class BankBranch {
private:
    string branchName;
    const BankTransaction* lastTransaction; 
public:
    BankBranch(string bName = "Центральное отделение (г. Минск)", const BankTransaction* trans = nullptr);

    void setLastTransaction(const BankTransaction* trans);
    void showBranchStatus() const;
};

void printTableHeader();
void printTableFooter();

// Менеджер банковских операций
template<typename Container>
class OperationManager {
private:
    Container data; // Контейнер

public:
    OperationManager() {}

    Container& getContainer() { return data; }
    const Container& getContainer() const { return data; }

    void displayAll() const {
        if (data.empty()) {
            setColor(12);
            cout << "Данный банковский реестр пуст.\n";
            setColor(7);
            return;
        }
        printTableHeader();
        for (typename Container::const_iterator it = data.begin(); it != data.end(); it++) {
            it->printRow();
        }
        printTableFooter();
    }

    void addTransaction(const BankTransaction& item) {
        data.push_back(item);
    }

    bool removeById(int searchId) {
        for (typename Container::iterator it = data.begin(); it != data.end(); it++) {
            if (it->getId() == searchId) {
                data.erase(it);
                return true;
            }
        }
        return false;
    }

    bool editTransaction(int id, double amt, const string& date, const string& acc, const string& name) {
        for (typename Container::iterator it = data.begin(); it != data.end(); it++) {
            if (it->getId() == id) {
                it->setAmount(amt);
                it->setDate(date);
                it->setAccount(BankAccount(acc, name));
                return true;
            }
        }
        return false;
    }

    void searchById(int searchId) const {
        bool found = false;
        for (typename Container::const_iterator it = data.begin(); it != data.end(); it++) {
            if (it->getId() == searchId) {
                if (!found) printTableHeader();
                it->printRow();
                found = true;
            }
        }
        if (found) printTableFooter();
        else {
            setColor(12);
            cout << "Транзакция с ID " << searchId << " в системе не найдена.\n";
            setColor(7);
        }
    }

    void filterByMinAmount(double minAmt) const {
        bool found = false;
        for (typename Container::const_iterator it = data.begin(); it != data.end(); it++) {
            if (it->getAmount() >= minAmt) {
                if (!found) printTableHeader();
                it->printRow();
                found = true;
            }
        }
        if (found) printTableFooter();
        else {
            setColor(12);
            cout << "Операций на сумму >= " << minAmt << " BYN не найдено.\n";
            setColor(7);
        }
    }

    void saveToFile(const string& filename) const {
        ofstream ofs(filename);
        if (!ofs.is_open()) {
            setColor(12);
            cout << "Ошибка! Не удалось открыть файл " << filename << " для записи.\n";
            setColor(7);
            return;
        }
        for (typename Container::const_iterator it = data.begin(); it != data.end(); it++) {
            ofs << *it;
        }
        if (ofs.bad()) {
            setColor(12);
            cout << "Ошибка при записи данных в файл!\n";
        }
        else {
            setColor(10);
            cout << "Данные успешно сохранены в файл: " << filename << endl;
        }
        ofs.close();
        setColor(7);
    }

    void loadFromFile(const string& filename) {
        ifstream ifs(filename);
        if (!ifs.is_open()) {
            setColor(12);
            cout << "Ошибка! Файл " << filename << " не найден или недоступен.\n";
            setColor(7);
            return;
        }

        data.clear();
        string line;
        while (getline(ifs, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            BankTransaction t;

            if (ss >> t) {
                data.push_back(t);
            }
            else {
                setColor(14);
                cout << "Предупреждение: Пропущена поврежденная строка.\n";
            }
        }

        if (ifs.bad()) {
            setColor(12);
            cout << "Критическая ошибка ввода-вывода при чтении файла!\n";
        }
        else {
            setColor(10);
            cout << "Загрузка завершена! Успешно загружено " << data.size() << " записей.\n";
        }

        ifs.close();
        setColor(7);
    }
};

void deleteFromVector(vector<BankTransaction>& vec, int id);
void deleteFromList(list<BankTransaction>& lst, int id);
int chooseSortType();
void runArrayMenu();

template <typename Container>
void runDynamicMenu(OperationManager<Container>& manager, string title, bool isVector) {
    int choice = -1;
    while (choice != 0) {
        setColor(11);
        cout << "\n======================================================\n";
        setColor(13);
        cout << "  " << title << "\n";
        setColor(11);
        cout << "======================================================\n";
        setColor(13);
        cout << "1 - Просмотреть все банковские операции\n";
        cout << "2 - Провести новую банковскую операцию (Добавить)\n";
        cout << "3 - Корректировка операции (Редактировать по ID)\n";
        cout << "4 - Отмена банковской операции (Удалить по ID)\n";
        cout << "5 - Поиск операции по ID\n";
        cout << "6 - Фильтр операций по минимальной сумме (BYN)\n";
        cout << "7 - Сортировка операций (по сумме или алфавиту)\n";
        cout << "8 - Экспорт данных в файл\n";
        cout << "9 - Импорт данных из файла\n";
        setColor(12);
        cout << "0 - Вернуться в Главное Меню Банка\n";
        setColor(7);

        choice = inputInt("Выберите действие: ");

        if (choice == 1) {
            manager.displayAll();
        }
        else if (choice == 2) {
            double amt = inputDouble("Введите сумму (BYN): ");
            string date = inputDateString("Введите дату операции (ДД.ММ.ГГГГ): ");
            string acc = inputAlphanumericString("Введите IBAN счет клиента: ");
            char nameBuf[100];
            inputString(nameBuf, 100, "Введите ФИО клиента: ");

            manager.addTransaction(BankTransaction(amt, date, BankAccount(acc, string(nameBuf))));
            setColor(10);
            cout << "Банковская операция успешно зарегистрирована!\n";
            setColor(7);
        }
        else if (choice == 3) {
            int id = inputInt("Введите ID операции для редактирования: ");
            double amt = inputDouble("Новая сумма (BYN): ");
            string date = inputDateString("Введите дату операции (ДД.ММ.ГГГГ): ");
            string acc = inputAlphanumericString("Новый IBAN счет: ");
            char nameBuf[100];
            inputString(nameBuf, 100, "Новое ФИО клиента: ");

            if (manager.editTransaction(id, amt, date, acc, string(nameBuf))) {
                setColor(10);
                cout << "Данные банковской операции успешно обновлены!\n";
                setColor(7);
            }
            else {
                setColor(12);
                cout << "Запись с таким ID не найдена.\n";
                setColor(7);
            }
        }
        else if (choice == 4) {
            int id = inputInt("Введите ID операции для отмены: ");
            if (manager.removeById(id)) {
                setColor(10);
                cout << "Транзакция с ID " << id << " успешно отменена!\n";
                setColor(7);
            }
            else {
                setColor(12);
                cout << "Транзакция с ID " << id << " не найдена.\n";
                setColor(7);
            }
        }
        else if (choice == 5) {
            int id = inputInt("Введите ID операции: ");
            manager.searchById(id);
        }
        else if (choice == 6) {
            double amt = inputDouble("Введите минимальный порог суммы (BYN): ");
            manager.filterByMinAmount(amt);
        }
        else if (choice == 7) {
            Container& cont = manager.getContainer();
            if (cont.empty()) {
                setColor(12);
                cout << "Контейнер пуст! Сортировка невозможна.\n";
                setColor(7);
                continue;
            }

            int sortType = chooseSortType();

            if (isVector) {
                vector<BankTransaction>& v = reinterpret_cast<vector<BankTransaction>&>(cont);
                for (size_t i = 0; i < v.size(); i++) {
                    for (size_t j = i + 1; j < v.size(); j++) {
                        bool condition = (sortType == 1)
                            ? (v[i] > v[j])
                            : (v[i].getAccount().getClientName() > v[j].getAccount().getClientName());

                        if (condition) {
                            BankTransaction temp = v[i];
                            v[i] = v[j];
                            v[j] = temp;
                        }
                    }
                }
            }
            else {
                list<BankTransaction>& l = reinterpret_cast<list<BankTransaction>&>(cont);
                if (sortType == 1) {
                    l.sort([](const BankTransaction& a, const BankTransaction& b) {
                        return a < b;
                        });
                }
                else {
                    l.sort([](const BankTransaction& a, const BankTransaction& b) {
                        return a.getAccount().getClientName() < b.getAccount().getClientName();
                        });
                }
            }
            setColor(10);
            if (sortType == 1) cout << "Данные отсортирован по возрастанию суммы!\n";
            else cout << "Данные отсортирован по алфавиту (ФИО клиента)!\n";
            setColor(7);
        }
        else if (choice == 8) {
            string fileName = isVector ? "fiz.txt" : "yur.txt";
            manager.saveToFile(fileName);
        }
        else if (choice == 9) {
            string fileName = isVector ? "fiz.txt" : "yur.txt";
            manager.loadFromFile(fileName);
        }
    }
}