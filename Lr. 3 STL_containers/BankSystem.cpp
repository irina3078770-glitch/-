#include "BankSystem.h"
#include <limits>
#include <windows.h>

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen() {
    system("cls");
}

int inputInt(const char* msg) {
    int v;
    while (true) {
        cout << msg;
        if (cin >> v && (cin.peek() == '\n' || cin.peek() == ' ')) {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return v;
        }
        setColor(12);
        cout << "Ошибка! Введите целое число.\n";
        setColor(7);
        cin.clear();
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
}

double inputDouble(const char* msg) {
    double v;
    while (true) {
        cout << msg;
        if (cin >> v && (cin.peek() == '\n' || cin.peek() == ' ')) {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return v;
        }
        setColor(12);
        cout << "Ошибка! Введите корректное число.\n";
        setColor(7);
        cin.clear();
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
}

void inputString(char* buffer, int maxLen, const char* msg) {
    while (true) {
        cout << msg;
        if (!cin.getline(buffer, maxLen)) {
            cin.clear();
            continue;
        }
        if (buffer[0] == '\0') {
            setColor(12);
            cout << "Ошибка! Строка не может быть пустой.\n";
            setColor(7);
            continue;
        }
        bool ok = true;
        for (int i = 0; buffer[i]; i++) {
            unsigned char c = buffer[i];
            if (c < 128 && !isalpha(c) && c != ' ')
                ok = false;
        }
        if (ok) break;
        setColor(12);
        cout << "Ошибка! Допускаются только буквы и пробелы.\n";
        setColor(7);
    }
}

string inputAlphanumericString(const char* msg) {
    string str;
    while (true) {
        cout << msg;
        getline(cin, str);
        if (!str.empty()) return str;
        setColor(12);
        cout << "Ошибка! Значение не может быть пустым.\n";
        setColor(7);
    }
}

string inputDateString(const char* msg) {
    string date;
    while (true) {
        cout << msg;
        getline(cin, date);

        if (date.length() != 10) {
            setColor(12);
            cout << "Ошибка! Дата должна быть формата ДД.ММ.ГГГГ (например, 16.10.2026).\n";
            setColor(7);
            continue;
        }

        if (date[2] != '.' || date[5] != '.') {
            setColor(12);
            cout << "Ошибка! Используйте точки в качестве разделителей (ДД.ММ.ГГГГ).\n";
            setColor(7);
            continue;
        }

        bool allDigits = true;
        for (int i = 0; i < 10; ++i) {
            if (i == 2 || i == 5) continue;
            if (!isdigit(static_cast<unsigned char>(date[i]))) {
                allDigits = false;
                break;
            }
        }

        if (!allDigits) {
            setColor(12);
            cout << "Ошибка! Числа даты должны состоять только из цифр.\n";
            setColor(7);
            continue;
        }

        int day = atoi(date.substr(0, 2).c_str());
        int month = atoi(date.substr(3, 2).c_str());
        int year = atoi(date.substr(6, 4).c_str());

        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0 || year > 2026) {
            setColor(12);
            cout << "Ошибка! Некорректный день (1..31), месяц (1..12) или год (1990..2099).\n";
            setColor(7);
            continue;
        }

        return date; 
    }
}

BankAccount::BankAccount(string accNum, string name) : accountNumber(accNum), clientName(name) {}
string BankAccount::getAccountNumber() const { return accountNumber; }
string BankAccount::getClientName() const { return clientName; }
void BankAccount::setAccountNumber(const string& acc) { accountNumber = acc; }
void BankAccount::setClientName(const string& name) { clientName = name; }
void BankAccount::printInfo() const {
    cout << left << setw(30) << accountNumber << setw(20) << clientName;
}

DepositAccount::DepositAccount(string accNum, string name, double rate) : BankAccount(accNum, name), interestRate(rate) {}
double DepositAccount::getInterestRate() const { return interestRate; }
void DepositAccount::setInterestRate(double rate) { interestRate = rate; }
void DepositAccount::printInfo() const {
    BankAccount::printInfo();
    cout << setw(10) << interestRate;
}

int BankTransaction::nextId = 1;

void BankTransaction::setNextId(int newNextId) { nextId = newNextId; }
int BankTransaction::getNextId() { return nextId; }

BankTransaction::BankTransaction(double amt, string d, BankAccount acc)
    : id(nextId++), amount(amt), date(d), account(acc) {
}

BankTransaction::BankTransaction(int tId, double amt, string d, BankAccount acc)
    : id(tId), amount(amt), date(d), account(acc) {
    if (tId >= nextId) {
        nextId = tId + 1;
    }
}int BankTransaction::getId() const { return id; }
double BankTransaction::getAmount() const { return amount; }
string BankTransaction::getDate() const { return date; }
BankAccount BankTransaction::getAccount() const { return account; }
void BankTransaction::setId(int newId) { id = newId; }
void BankTransaction::setAmount(double amt) { amount = amt; }
void BankTransaction::setDate(const string& d) { date = d; }
void BankTransaction::setAccount(const BankAccount& acc) { account = acc; }

void BankTransaction::printRow() const {
    cout << "| " << setw(6) << id
        << " | " << setw(10) << fixed << setprecision(2) << amount << " BYN"
        << " | " << setw(10) << date
        << " | " << setw(28) << account.getAccountNumber()
        << " | " << setw(28) << account.getClientName() << " |" << endl;
}

bool BankTransaction::operator<(const BankTransaction& other) const {
    return this->amount < other.amount;
}

bool BankTransaction::operator>(const BankTransaction& other) const {
    return this->amount > other.amount;
}

bool BankTransaction::operator==(const BankTransaction& other) const {
    return this->amount == other.amount;
}

ostream& operator<<(ostream& os, const BankTransaction& t) {
    os << t.id << "|"
        << t.amount << "|"
        << t.date << "|"
        << t.account.getAccountNumber() << "|"
        << t.account.getClientName() << "\n";
    return os;
}

istream& operator>>(istream& is, BankTransaction& t) {
    string strId, strAmt, date, acc, name;

    if (getline(is, strId, '|') &&
        getline(is, strAmt, '|') &&
        getline(is, date, '|') &&
        getline(is, acc, '|') &&
        getline(is, name)) { 

        t.id = atoi(strId.c_str());
        t.amount = atof(strAmt.c_str());
        t.date = date;
        t.account = BankAccount(acc, name);
    }
    return is;
}

BankBranch::BankBranch(string bName, const BankTransaction* trans)
    : branchName(bName), lastTransaction(trans) {
}
void BankBranch::setLastTransaction(const BankTransaction* trans) { lastTransaction = trans; }
void BankBranch::showBranchStatus() const {
    setColor(13); 
    cout << "Филиал банка: " << branchName << endl;
    if (lastTransaction) {
        cout << "Последняя обработанная транзакция (ID): " << lastTransaction->getId()
            << " на сумму " << lastTransaction->getAmount() << " BYN" << endl;
    }
    else {
        cout << "Зарегистрированных транзакций нет." << endl;
    }
    setColor(7);
}

void printTableHeader() {
    setColor(13);
    cout << "+" << string(8, '-') << "+" << string(16, '-') << "+" << string(12, '-')
        << "+" << string(30, '-') << "+" << string(30, '-') << "+" << endl;
    cout << "| " << left << setw(6) << "ID"
        << " | " << setw(14) << "Сумма (BYN)"
        << " | " << setw(10) << "Дата"
        << " | " << setw(28) << "IBAN Счет"
        << " | " << setw(28) << "Клиент" << " |" << endl;
    cout << "+" << string(8, '-') << "+" << string(16, '-') << "+" << string(12, '-')
        << "+" << string(30, '-') << "+" << string(30, '-') << "+" << endl;
    setColor(7);
}

void printTableFooter() {
    setColor(13);
    cout << "+" << string(8, '-') << "+" << string(16, '-') << "+" << string(12, '-')
        << "+" << string(30, '-') << "+" << string(30, '-') << "+" << endl;
    setColor(7);
}

void deleteFromVector(vector<BankTransaction>& vec, int id) {
    bool found = false;

    for (vector<BankTransaction>::iterator it = vec.begin(); it != vec.end(); ) {
        if (it->getId() == id) {
            it = vec.erase(it);
            found = true;
            break;
        }
        else {
            ++it;
        }
    }

    if (found) {
        setColor(10);
        cout << "Банковская операция с ID " << id << " успешно отменена (удалена).\n";
        setColor(7);
    }
    else {
        setColor(12);
        cout << "Ошибка! Транзакция с ID " << id << " не найдена.\n";
        setColor(7);
    }
}

void deleteFromList(list<BankTransaction>& lst, int id) {
    bool found = false;

    for (list<BankTransaction>::iterator it = lst.begin(); it != lst.end(); ) {
        if (it->getId() == id) {
            it = lst.erase(it);
            found = true;
            break;
        }
        else {
            ++it;
        }
    }

    if (found) {
        setColor(10);
        cout << "Банковская операция с ID " << id << " успешно отменена (удалена).\n";
        setColor(7);
    }
    else {
        setColor(12);
        cout << "Ошибка! Транзакция с ID " << id << " не найдена.\n";
        setColor(7);
    }
}

int chooseSortType() {
    setColor(13);
    cout << "\nВыберите критерий сортировки:\n";
    cout << "1. По сумме операции (по возрастанию, BYN)\n";
    cout << "2. По алфавиту (ФИО клиента, А-Я)\n";
    setColor(7);
    int type = inputInt("Ваш выбор: ");
    return (type == 2) ? 2 : 1;
}

void runArrayMenu() {
    const size_t SIZE = 3;
    array<BankTransaction, SIZE> arr = {
        BankTransaction(101, 2500.50, "16.10.2026", BankAccount("BY12UNBS30120000000000000001", "Иванов И.И.")),
        BankTransaction(102, 10400.00, "16.10.2026", BankAccount("BY88UNBS30120000000000000002", "Абрамов А.А.")),
        BankTransaction(103, 120.00,  "16.10.2026", BankAccount("BY44UNBS30120000000000000003", "Петров П.П."))
    };

    int choice = -1;
    while (choice != 0) {
        setColor(11);
        cout << "\n======================================================\n";
        setColor(13);
        cout << "  ДНЕВНОЙ РЕЕСТР ВАЛЮТНЫХ ЛИМИТОВ (std::array, N=3)\n";
        setColor(11);
        cout << "======================================================\n";
        setColor(13);
        cout << "1 - Посмотреть записи лимитов за смену\n";
        cout << "2 - Корректировать лимит по индексу \n";
        cout << "3 - Сортировать лимиты (по сумме или алфавиту)\n";
        cout << "4 - Сохранить дневной отчет в файл\n";
        setColor(12);
        cout << "0 - Назад\n";
        setColor(7);

        choice = inputInt("Выберите действие: ");
        clearScreen();

        if (choice == 1) {
            printTableHeader();
            for (size_t i = 0; i < SIZE; i++) arr[i].printRow();
            printTableFooter();
        }
        else if (choice == 2) {
            int userNum = inputInt("Введите номер записи для редактирования (1..3): ");

            int idx = userNum - 1;

            if (idx >= 0 && idx < static_cast<int>(SIZE)) {
                int id = inputInt("Введите ID: ");
                double amt = inputDouble("Введите сумму (BYN): ");
                string date = inputDateString("Введите дату операции (ДД.ММ.ГГГГ): ");
                string acc = inputAlphanumericString("Введите IBAN счет: ");
                char nameBuf[100];
                inputString(nameBuf, 100, "Введите ФИО клиента: ");

                arr[idx] = BankTransaction(id, amt, date, BankAccount(acc, string(nameBuf)));

                setColor(10);
                cout << "Запись лимита №" << userNum << " успешно обновлена!\n";
                setColor(7);
            }
            else {
                setColor(12);
                cout << "Ошибка! Номер записи должен быть от 1 до 3.\n";
                setColor(7);
            }
        }
        else if (choice == 3) {
            int sortType = chooseSortType();
            clearScreen();

            for (size_t i = 0; i < SIZE; i++) {
                for (size_t j = i + 1; j < SIZE; j++) {
                    bool condition = (sortType == 1)
                        ? (arr[i] > arr[j])
                        : (arr[i].getAccount().getClientName() > arr[j].getAccount().getClientName());

                    if (condition) {
                        BankTransaction temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                }
            }
            setColor(10);
            if (sortType == 1) cout << "Лимиты отсортированы по возрастанию суммы!\n";
            else cout << "Лимиты отсортированы по алфавиту (ФИО клиента)!\n";
            setColor(7);
        }
        else if (choice == 4) {
            ofstream ofs("Daily_Limits.txt");
            if (ofs.is_open()) {
                for (size_t i = 0; i < SIZE; i++) {
                    ofs << arr[i];
                }
                ofs.close();
                setColor(10);
                cout << "Данные сохранены в файл Daily_Limits.txt\n";
                setColor(7);
            }
            else {
                setColor(12);
                cout << "Ошибка открытия файла!\n";
                setColor(7);
            }
        }
    }
}