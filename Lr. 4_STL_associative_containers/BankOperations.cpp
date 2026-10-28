#include "BankOperations.h"

BankAccount::BankAccount(string accNum, string name) : accountNumber(accNum), clientName(name) {}

void BankAccount::printInfo() const {
    cout << left << setw(28) << accountNumber << setw(22) << clientName;
}

DepositAccount::DepositAccount(string accNum, string name, double rate)
    : BankAccount(accNum, name), interestRate(rate) {
}

void DepositAccount::printInfo() const {
    BankAccount::printInfo();
    cout << setw(10) << interestRate << "%";
}

BankTransaction::BankTransaction() : id(0), amount(0.0), date("01.01.2026"), account() {}

BankTransaction::BankTransaction(int id, double amount, string date, BankAccount acc)
    : id(id), amount(amount), date(date), account(acc) {
}

void BankTransaction::inputData() {
    string accNum = BankManager::inputString("Введите IBAN счета (например, BY13OLMP...): ");
    string name = BankManager::inputString("Введите ФИО клиента: ");

    account = BankAccount(accNum, name);

    amount = BankManager::inputDouble("Введите сумму операции (BYN): ");
    date = BankManager::inputString("Введите дату (ДД.ММ.ГГГГ): ");
}

ostream& operator<<(ostream& os, const BankTransaction& tx) {
    os << left
        << "| " << setw(6) << tx.id
        << "| " << setw(12) << fixed << setprecision(2) << tx.amount << " BYN"
        << "| " << setw(12) << tx.date
        << "| " << setw(26) << tx.account.getAccountNumber()
        << "| " << setw(30) << tx.account.getClientName() << " |";
    return os;
}

istream& operator>>(istream& is, BankTransaction& tx) {
    string line;
    if (getline(is, line)) {
        if (line.empty()) return is;

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);

        if (p1 != string::npos && p2 != string::npos && p3 != string::npos) {
            tx.id = stoi(line.substr(0, p1));
            tx.amount = stod(line.substr(p1 + 1, p2 - p1 - 1));
            tx.date = line.substr(p2 + 1, p3 - p2 - 1);

            string acc, name;
            if (p4 != string::npos) {
                acc = line.substr(p3 + 1, p4 - p3 - 1);
                name = line.substr(p4 + 1);
            }
            else {
                acc = line.substr(p3 + 1);
                name = "Неизвестно";
            }
            tx.account = BankAccount(acc, name);
        }
    }
    return is;
}

// --- Реализация BankBranch (Агрегация) ---
BankBranch::BankBranch(string bName, const BankTransaction* trans)
    : branchName(bName), lastTransaction(trans) {
}

void BankBranch::showBranchStatus() const {
    setColor(CLR_MAGENTA);
    cout << "\nФилиал банка: " << branchName << "\n";
    if (lastTransaction) {
        cout << "Последняя операция (ID: " << lastTransaction->getId()
            << ") на сумму " << lastTransaction->getAmount() << " BYN\n";
    }
    else {
        cout << "Операций в филиале пока нет.\n";
    }
    setColor(CLR_DEFAULT);
}

// --- Реализация BankManager ---
BankManager::BankManager() : nextId(1) {}

int BankManager::inputInt(const string& prompt) {
    int val;
    while (true) {
        setColor(CLR_CYAN);
        cout << prompt;
        setColor(CLR_DEFAULT);
        if (cin >> val) {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return val;
        }
        setColor(CLR_RED);
        cout << "Ошибка! Введите целое число.\n";
        setColor(CLR_DEFAULT);
        cin.clear();
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
}

double BankManager::inputDouble(const string& prompt) {
    double val;
    while (true) {
        setColor(CLR_CYAN);
        cout << prompt;
        setColor(CLR_DEFAULT);
        if (cin >> val && val >= 0) {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return val;
        }
        setColor(CLR_RED);
        cout << "Ошибка! Введите положительное число.\n";
        setColor(CLR_DEFAULT);
        cin.clear();
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
}

string BankManager::inputString(const string& prompt) {
    string str;
    while (true) {
        setColor(CLR_CYAN);
        cout << prompt;
        setColor(CLR_DEFAULT);
        getline(cin, str);
        if (!str.empty()) return str;
        setColor(CLR_RED);
        cout << "Ошибка! Строка не может быть пустой.\n";
        setColor(CLR_DEFAULT);
    }
}

void BankManager::addTransaction(BankTransaction tx) {
    tx.setId(nextId++);

    mapTx[tx.getId()] = tx;
    setAccounts.insert(tx.getAccount().getAccountNumber());
    multimapAccTx.insert(make_pair(tx.getAccount().getAccountNumber(), tx));
    multisetAmounts.insert(tx.getAmount());
    unMapTx[tx.getId()] = tx;
    unSetVerifiedAccs.insert(tx.getAccount().getAccountNumber());
    unMultiMapNameTx.insert(make_pair(toLowerStr(tx.getAccount().getClientName()), tx));
    unMultiSetAmounts.insert(tx.getAmount());

    setColor(CLR_GREEN);
    cout << "УСПЕХ! Транзакция зарегистрирована под ID: " << tx.getId() << "\n";
    setColor(CLR_DEFAULT);
}

bool BankManager::removeTransaction(int id) {
    map<int, BankTransaction>::iterator it = mapTx.find(id);
    if (it == mapTx.end()) {
        setColor(CLR_RED);
        cout << "ОШИБКА! Транзакция с ID " << id << " не найдена!\n";
        setColor(CLR_DEFAULT);
        return false;
    }

    // Удаляем и пересобираем контейнеры
    mapTx.erase(id);
    unMapTx.erase(id);

    multimapAccTx.clear();
    multisetAmounts.clear();
    unMultiMapNameTx.clear();
    unMultiSetAmounts.clear();
    setAccounts.clear();
    unSetVerifiedAccs.clear();

    for (map<int, BankTransaction>::iterator p = mapTx.begin(); p != mapTx.end(); ++p) {
        setAccounts.insert(p->second.getAccount().getAccountNumber());
        multimapAccTx.insert(make_pair(p->second.getAccount().getAccountNumber(), p->second));
        multisetAmounts.insert(p->second.getAmount());
        unSetVerifiedAccs.insert(p->second.getAccount().getAccountNumber());
        unMultiMapNameTx.insert(make_pair(toLowerStr(p->second.getAccount().getClientName()), p->second));
        unMultiSetAmounts.insert(p->second.getAmount());
    }

    setColor(CLR_GREEN);
    cout << "УСПЕХ! Транзакция удалена.\n";
    setColor(CLR_DEFAULT);
    return true;
}

bool BankManager::editTransaction(int id) {
    map<int, BankTransaction>::iterator it = mapTx.find(id);
    if (it == mapTx.end()) {
        setColor(CLR_RED);
        cout << "ОШИБКА! Транзакция не найдена!\n";
        setColor(CLR_DEFAULT);
        return false;
    }

    string acc = inputString("Новый IBAN счета: ");
    string name = inputString("Новое ФИО клиента: ");
    double amount = inputDouble("Новая сумма (BYN): ");
    string date = inputString("Новая дата (ДД.ММ.ГГГГ): ");

    removeTransaction(id);
    BankTransaction updatedTx(id, amount, date, BankAccount(acc, name));

    mapTx[id] = updatedTx;
    setAccounts.insert(acc);
    multimapAccTx.insert(make_pair(acc, updatedTx));
    multisetAmounts.insert(amount);
    unMapTx[id] = updatedTx;
    unSetVerifiedAccs.insert(acc);
    unMultiMapNameTx.insert(make_pair(toLowerStr(name), updatedTx));
    unMultiSetAmounts.insert(amount);

    setColor(CLR_GREEN);
    cout << "УСПЕХ! Данные транзакции обновлены.\n";
    setColor(CLR_DEFAULT);
    return true;
}

void BankManager::printHeader() const {
    setColor(CLR_BLUE);
    cout << "---------------------------------------------------------------------------------------\n";
    cout << left << setw(10) << "ID"
        << setw(20) << "Сумма"
        << setw(14) << "Дата"
        << setw(26) << "IBAN Счет"
        << setw(22) << "Клиент" << "\n";
    cout << "---------------------------------------------------------------------------------------\n";
    setColor(CLR_DEFAULT);
}

void BankManager::displayAllMap() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Справочник операций по ID ---\n";
    setColor(CLR_DEFAULT);
    if (mapTx.empty()) { cout << "Список пуст.\n"; return; }
    printHeader();
    for (map<int, BankTransaction>::const_iterator it = mapTx.begin(); it != mapTx.end(); ++it) {
        cout << it->second << "\n";
    }
}

void BankManager::displayAllSet() const {
    setColor(CLR_MAGENTA);
    cout << "\n---  Уникальные счета клиентов (отсортированы) ---\n";
    setColor(CLR_DEFAULT);
    if (setAccounts.empty()) { cout << "Счетов нет.\n"; return; }
    int i = 1;
    for (set<string>::const_iterator it = setAccounts.begin(); it != setAccounts.end(); ++it) {
        cout << i++ << ". Счет: ";
        setColor(CLR_CYAN); 
        cout << *it;
        setColor(CLR_DEFAULT); 
        cout << "\n";
    }
}

void BankManager::displayAllMultiMap() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- История операций по счетам ---\n";
    setColor(CLR_DEFAULT);
    if (multimapAccTx.empty()) { cout << "Истории нет.\n"; return; }
    printHeader();
    for (multimap<string, BankTransaction>::const_iterator it = multimapAccTx.begin(); it != multimapAccTx.end(); ++it) {
        cout << it->second << "\n";
    }
}

void BankManager::displayAllMultiSet() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Суммы операций (по возрастанию) ---\n";
    setColor(CLR_DEFAULT);
    if (multisetAmounts.empty()) { cout << "Данных нет.\n"; return; }
    for (multiset<double>::const_iterator it = multisetAmounts.begin(); it != multisetAmounts.end(); ++it) {
        setColor(CLR_GREEN);
        cout << fixed << setprecision(2) << *it << " BYN  ";
    }
    setColor(CLR_DEFAULT);
    cout << "\n";
}

void BankManager::displayAllUnorderedMap() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Хеш-реестр операций по ID ---\n";
    setColor(CLR_DEFAULT);
    if (unMapTx.empty()) { cout << "Реестр пуст.\n"; return; }
    printHeader();
    for (unordered_map<int, BankTransaction>::const_iterator it = unMapTx.begin(); it != unMapTx.end(); ++it) {
        cout << it->second << "\n";
    }
}

void BankManager::displayAllUnorderedSet() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Хеш-набор проверенных счетов ---\n";
    setColor(CLR_DEFAULT);
    if (unSetVerifiedAccs.empty()) { cout << "Счетов нет.\n"; return; }
    for (unordered_set<string>::const_iterator it = unSetVerifiedAccs.begin(); it != unSetVerifiedAccs.end(); ++it) {
        cout << " - ";
        setColor(CLR_CYAN); 
        cout << *it; 
        setColor(CLR_DEFAULT);
        cout << "\n";
    }
}

void BankManager::displayAllUnorderedMultiMap() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Группировка операций по клиентам ---\n";
    setColor(CLR_DEFAULT);
    if (unMultiMapNameTx.empty()) { cout << "Данных нет.\n"; return; }
    printHeader();
    for (unordered_multimap<string, BankTransaction>::const_iterator it = unMultiMapNameTx.begin(); it != unMultiMapNameTx.end(); ++it) {
        cout << it->second << "\n";
    }
}

void BankManager::displayAllUnorderedMultiSet() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Неупорядоченные суммы ---\n";
    setColor(CLR_DEFAULT);
    if (unMultiSetAmounts.empty()) { cout << "Данных нет.\n"; return; }
    for (unordered_multiset<double>::const_iterator it = unMultiSetAmounts.begin(); it != unMultiSetAmounts.end(); ++it) {
        setColor(CLR_YELLOW);
        cout << "[" << fixed << setprecision(2) << *it << " BYN] ";
    }
    setColor(CLR_DEFAULT);
    cout << "\n";
}

void BankManager::searchById(int id) const {
    map<int, BankTransaction>::const_iterator it = mapTx.find(id);
    if (it != mapTx.end()) {
        setColor(CLR_GREEN);
        cout << "\nРЕЗУЛЬТАТ ПОИСКА:\n";
        setColor(CLR_DEFAULT);
        printHeader();
        cout << it->second << "\n";
    }
    else {
        setColor(CLR_RED);
        cout << "\nТранзакция с ID " << id << " не найдена.\n";
        setColor(CLR_DEFAULT);
    }
}

void BankManager::filterByAmount(double minAmount) const {
    setColor(CLR_YELLOW);
    cout << "\n--- Фильтр: Операции от " << minAmount << " BYN ---\n";
    setColor(CLR_DEFAULT);
    printHeader();
    bool found = false;
    for (map<int, BankTransaction>::const_iterator it = mapTx.begin(); it != mapTx.end(); ++it) {
        if (it->second.getAmount() >= minAmount) {
            cout << it->second << "\n";
            found = true;
        }
    }
    if (!found) cout << "Подходящих операций не найдено.\n";
}

bool BankManager::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        setColor(CLR_RED);
        cout << "Ошибка открытия файла для записи!\n";
        setColor(CLR_DEFAULT);
        return false;
    }

    for (map<int, BankTransaction>::const_iterator it = mapTx.begin(); it != mapTx.end(); ++it) {
        file << it->second.getId() << "|"
            << it->second.getAmount() << "|"
            << it->second.getDate() << "|"
            << it->second.getAccount().getAccountNumber() << "|"
            << it->second.getAccount().getClientName() << "\n";
    }

    file.close();
    setColor(CLR_GREEN);
    cout << "Данные успешно сохранены в файл: " << filename << "\n";
    setColor(CLR_DEFAULT);
    return true;
}

bool BankManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        setColor(CLR_RED);
        cout << "Файл не найден или не может быть открыт!\n";
        setColor(CLR_DEFAULT);
        return false;
    }

    // Очищаем все контейнеры перед загрузкой новых данных
    mapTx.clear();
    setAccounts.clear();
    multimapAccTx.clear();
    multisetAmounts.clear();
    unMapTx.clear();
    unSetVerifiedAccs.clear();
    unMultiMapNameTx.clear();
    unMultiSetAmounts.clear();
    nextId = 1;

    string line;
    int maxId = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);

        if (p1 == string::npos || p2 == string::npos || p3 == string::npos || p4 == string::npos)
            continue;

        int id = atoi(line.substr(0, p1).c_str());
        double amount = atof(line.substr(p1 + 1, p2 - p1 - 1).c_str());
        string date = line.substr(p2 + 1, p3 - p2 - 1);
        string acc = line.substr(p3 + 1, p4 - p3 - 1); 
        string name = line.substr(p4 + 1); 

        if (id > maxId) maxId = id;
        BankTransaction tx(id, amount, date, BankAccount(acc, name));

        mapTx[id] = tx;
        setAccounts.insert(acc);
        multimapAccTx.insert(make_pair(acc, tx));
        multisetAmounts.insert(amount);
        unMapTx[id] = tx;
        unSetVerifiedAccs.insert(acc);
        unMultiMapNameTx.insert(make_pair(toLowerStr(name), tx));
        unMultiSetAmounts.insert(amount);
    }

    nextId = maxId + 1;
    file.close();
    setColor(CLR_GREEN);
    cout << "Данные успешно загружены из файла!\n";
    setColor(CLR_DEFAULT);
    return true;
}