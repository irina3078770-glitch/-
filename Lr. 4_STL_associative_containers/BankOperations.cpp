#include "BankOperations.h"

BankTransaction::BankTransaction() : id(0), accountNumber(""), type(""), amount(0.0), comission(0.0) {}

BankTransaction::BankTransaction(int id, string accNum, string type, double amount, double comission)
    : id(id), accountNumber(accNum), type(type), amount(amount), comission(comission) {
}

void BankTransaction::inputData() {
    accountNumber = BankManager::inputString("Введите номер счета (например BY13OLMP3812): ");
    type = BankManager::inputString("Введите тип операции (Перевод/Снятие/Пополнение): ");
    amount = BankManager::inputDouble("Введите сумму операции (BYN): ");
    comission = BankManager::inputDouble("Введите комиссию банка (BYN): ");
}

ostream& operator<<(ostream& os, const BankTransaction& tx) {
    os << left
        << "| " << setw(6) << tx.id
        << "| " << setw(16) << tx.accountNumber
        << "| " << setw(14) << tx.type
        << "| " << setw(12) << fixed << setprecision(2) << tx.amount
        << "| " << setw(10) << tx.comission << " |";
    return os;
}

istream& operator>>(istream& is, BankTransaction& tx) {
    is >> tx.id >> tx.accountNumber >> tx.type >> tx.amount >> tx.comission;
    return is;
}

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
    setAccounts.insert(tx.getAccountNumber());
    multimapAccTx.insert(make_pair(tx.getAccountNumber(), tx));
    multisetAmounts.insert(tx.getAmount());
    unMapTx[tx.getId()] = tx;
    unSetVerifiedAccs.insert(tx.getAccountNumber());

    unMultiMapTypeTx.insert(make_pair(toLowerStr(tx.getType()), tx));
    unMultiSetCom.insert(tx.getCom());

    setColor(CLR_GREEN);
    cout << "УСПЕХ! Транзакция добавлена с ID: " << tx.getId() << "\n";
    setColor(CLR_DEFAULT);
}

bool BankManager::removeTransaction(int id) {
    map<int, BankTransaction>::iterator it = mapTx.find(id);
    if (it == mapTx.end()) {
        setColor(CLR_RED);
        cout << "ОШИБКА! Транзакция не найдена!\n";
        setColor(CLR_DEFAULT);
        return false;
    }

    mapTx.erase(id);
    unMapTx.erase(id);

    multimapAccTx.clear();
    multisetAmounts.clear();
    unMultiMapTypeTx.clear();
    unMultiSetCom.clear();

    map<int, BankTransaction>::iterator p = mapTx.begin();
    for (p; p != mapTx.end(); p++) {
        multimapAccTx.insert(make_pair(p->second.getAccountNumber(), p->second));
        multisetAmounts.insert(p->second.getAmount());
        unMultiMapTypeTx.insert(make_pair(toLowerStr(p->second.getType()), p->second));
        unMultiSetCom.insert(p->second.getCom());
    }

    setColor(CLR_GREEN);
    cout << "УСПЕХ! Операция удалена.\n";
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

    string newAcc = inputString("Новый номер счета: ");
    string newType = inputString("Новый тип операции: ");
    double newAmount = inputDouble("Новая сумма (BYN): ");
    double newCom = inputDouble("Новая комиссия (BYN): ");

    removeTransaction(id);

    BankTransaction updatedTx(id, newAcc, newType, newAmount, newCom);

    mapTx[id] = updatedTx;
    setAccounts.insert(newAcc);
    multimapAccTx.insert(make_pair(newAcc, updatedTx));
    multisetAmounts.insert(newAmount);
    unMapTx[id] = updatedTx;
    unSetVerifiedAccs.insert(newAcc);
    unMultiMapTypeTx.insert(make_pair(toLowerStr(newType), updatedTx));
    unMultiSetCom.insert(newCom);

    setColor(CLR_GREEN);
    cout << "УСПЕХ! Данные обновлены!\n";
    setColor(CLR_DEFAULT);
    return true;
}

void BankManager::printHeader() const {
    setColor(CLR_BLUE);
    cout << "----------------------------------------------------------------------\n";
    cout << left << setw(8) << "ID"
        << setw(18) << "Номер счета"
        << setw(16) << "Тип операции"
        << setw(14) << "Сумма (BYN)"
        << setw(12) << "Комиссия (BYN)" << "\n";
    cout << "----------------------------------------------------------------------\n";
    setColor(CLR_DEFAULT);
}

void BankManager::displayAllMap() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Справочник операций по ID ---\n";
    setColor(CLR_DEFAULT);
    if (mapTx.empty()) { 
        cout << "Операций нет.\n"; 
        return;
    }
    printHeader();

    map<int, BankTransaction>::const_iterator it = mapTx.begin();
    for (it; it != mapTx.end(); it++) {
        cout << it->second << "\n";
    }
}

void BankManager::displayAllSet() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Уникальные счета клиентов ---\n";
    setColor(CLR_DEFAULT);
    if (setAccounts.empty()) { 
        cout << "Счетов клиентов нет.\n"; 
        return; 
    }

    int i = 1;
    set<string>::const_iterator it = setAccounts.begin();
    for (it; it != setAccounts.end(); it++) {
        cout << i++ << ". Счет: " << CLR_CYAN << *it << CLR_DEFAULT << "\n";
    }
}

void BankManager::displayAllMultiMap() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- История операций по счетам ---\n";
    setColor(CLR_DEFAULT);
    if (multimapAccTx.empty()) { 
        cout << "Операции не найдены.\n"; 
        return; 
    }
    printHeader();

    multimap<string, BankTransaction>::const_iterator it = multimapAccTx.begin();
    for (it; it != multimapAccTx.end(); it++) {
        cout << it->second << "\n";
    }
}

void BankManager::displayAllMultiSet() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Отсортированные суммы транзакций ---\n";
    setColor(CLR_DEFAULT);
    if (multisetAmounts.empty()) { 
        cout << "Транзакции не найдены.\n"; 
        return; 
    }

    multiset<double>::const_iterator it = multisetAmounts.begin();
    for (it; it != multisetAmounts.end(); it++) {
        setColor(CLR_GREEN);
        cout  << fixed << setprecision(2) << *it << " BYN ";
    }
    setColor(CLR_DEFAULT);
    cout << "\n";
}

void BankManager::displayAllUnorderedMap() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Быстрый индекс операций ---\n";
    setColor(CLR_DEFAULT);
    if (unMapTx.empty()) { 
        cout << "Операции не найдены.\n"; 
        return; 
    }
    printHeader();

    unordered_map<int, BankTransaction>::const_iterator it = unMapTx.begin();
    for (it; it != unMapTx.end(); it++) {
        cout << it->second << "\n";
    }
}

void BankManager::displayAllUnorderedSet() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Список счетов ---\n";
    setColor(CLR_DEFAULT);
    if (unSetVerifiedAccs.empty()) { 
        cout << "Счета не найдены.\n"; 
        return; 
    }

    unordered_set<string>::const_iterator it = unSetVerifiedAccs.begin();
    for (it; it != unSetVerifiedAccs.end(); it++) {
        cout << " - Счет: " << CLR_CYAN << *it << CLR_DEFAULT << "\n";
    }
}

void BankManager::displayAllUnorderedMultiMap() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Группировка по категориям ---\n";
    setColor(CLR_DEFAULT);
    if (unMultiMapTypeTx.empty()) { 
        cout << "Операции не найдены.\n";
        return;
    }
    printHeader();

    unordered_multimap<string, BankTransaction>::const_iterator it = unMultiMapTypeTx.begin();
    for (it; it != unMultiMapTypeTx.end(); it++) {
        cout << it->second << "\n";
    }
}

void BankManager::displayAllUnorderedMultiSet() const {
    setColor(CLR_MAGENTA);
    cout << "\n--- Комиссии банка ---\n";
    setColor(CLR_DEFAULT);
    if (unMultiSetCom.empty()) { 
        cout << "Комиссии не найдены.\n";
        return;
    }

    unordered_multiset<double>::const_iterator it = unMultiSetCom.begin();
    for (; it != unMultiSetCom.end(); it++) {
        setColor(CLR_YELLOW);
        cout << "(Комиссия: " << fixed << setprecision(2) << *it << " BYN) ";
    }
    setColor(CLR_DEFAULT);
    cout << "\n";
}

void BankManager::searchById(int id) const {
    map<int, BankTransaction>::const_iterator it = mapTx.find(id);
    if (it != mapTx.end()) {
        setColor(CLR_GREEN);
        cout << "\nНАЙДЕНО:\n";
        setColor(CLR_DEFAULT);
        printHeader();
        cout << it->second << "\n";
    }
    else {
        setColor(CLR_RED);
        cout << "\nОШИБКА! Запись не найдена.\n";
        setColor(CLR_DEFAULT);
    }
}

void BankManager::filterByAmount(double minAmount) const {
    setColor(CLR_YELLOW);
    cout << "\n--- Операции на сумму от " << minAmount << " BYN ---\n";
    setColor(CLR_DEFAULT);
    printHeader();
    bool found = false;

    map<int, BankTransaction>::const_iterator it = mapTx.begin();
    for (it; it != mapTx.end(); it++) {
        if (it->second.getAmount() >= minAmount) {
            cout << it->second << "\n";
            found = true;
        }
    }
    if (!found) cout << "Операции не найдены.\n";
}

bool BankManager::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) return false;

    map<int, BankTransaction>::const_iterator it = mapTx.begin();
    for (it; it != mapTx.end(); it++) {
        file << it->second.getId() << " "
            << it->second.getAccountNumber() << " "
            << it->second.getType() << " "
            << it->second.getAmount() << " "
            << it->second.getCom() << "\n";
    }
    file.close();
    setColor(CLR_GREEN);
    cout << "Данные сохранены в файл.\n";
    setColor(CLR_DEFAULT);
    return true;
}

bool BankManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    mapTx.clear();
    setAccounts.clear();
    multimapAccTx.clear();
    multisetAmounts.clear();
    unMapTx.clear();
    unSetVerifiedAccs.clear();
    unMultiMapTypeTx.clear();
    unMultiSetCom.clear();
    nextId = 1;

    BankTransaction tx;
    int maxId = 0;
    while (file >> tx) {
        if (tx.getId() >= maxId) maxId = tx.getId();
        mapTx[tx.getId()] = tx;
        setAccounts.insert(tx.getAccountNumber());
        multimapAccTx.insert(make_pair(tx.getAccountNumber(), tx));
        multisetAmounts.insert(tx.getAmount());
        unMapTx[tx.getId()] = tx;
        unSetVerifiedAccs.insert(tx.getAccountNumber());
        unMultiMapTypeTx.insert(make_pair(toLowerStr(tx.getType()), tx));
        unMultiSetCom.insert(tx.getCom());
    }
    nextId = maxId + 1;
    file.close();
    if (mapTx.empty()) {
        setColor(CLR_YELLOW);
        cout << "Файл '" << filename << "' пуст или содержит некорректные данные.\n";
        setColor(CLR_DEFAULT);
        return true;
    }
    setColor(CLR_GREEN);
    cout << "Данные загружены из файла.\n";
    setColor(CLR_DEFAULT);
    return true;
}