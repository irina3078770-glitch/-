#include "BankOperations.h"

vector<pair<int, BankOperation::OperationFactoryFunc> > BankOperation::operationRegistry;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
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

string inputString(const char* msg) {
    string str;
    while (true) {
        cout << msg;
        getline(cin, str);
        if (str.empty()) {
            setColor(12);
            cout << "Ошибка! Поле не может быть пустым.\n";
            setColor(7);
            continue;
        }
        bool ok = true;
        for (size_t i = 0; i < str.length(); i++) {
            unsigned char c = static_cast<unsigned char>(str[i]);
            if (c < 128 && !isalpha(c) && c != ' ') {
                ok = false;
                break;
            }
        }
        if (ok) return str;
        setColor(12);
        cout << "Ошибка! Только буквы и пробелы.\n";
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
        if (date.length() != 10 || date[2] != '.' || date[5] != '.') {
            setColor(12);
            cout << "Ошибка! Формат даты: ДД.ММ.ГГГГ (например, 16.10.2026).\n";
            setColor(7);
            continue;
        }
        int day = atoi(date.substr(0, 2).c_str());
        int month = atoi(date.substr(3, 2).c_str());
        int year = atoi(date.substr(6, 4).c_str());
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1990 || year > 2026) {
            setColor(12);
            cout << "Ошибка! Проверьте корректность дня, месяца или года.\n";
            setColor(7);
            continue;
        }
        return date;
    }
}

int generateUniqueOperationId(const vector<unique_ptr<BankOperation> >& ops) {
    int newId;
    bool exists;
    do {
        exists = false;
        newId = 1 + rand() % 9999;
        for (size_t i = 0; i < ops.size(); i++) {
            if (ops[i] != nullptr && ops[i]->getId() == newId) {
                exists = true;
                break;
            }
        }
    } while (exists);
    return newId;
}

static double inputPositiveAmount(const char* msg) {
    while (true) {
        double val = inputDouble(msg);
        if (val > 0.0) return val;
        setColor(12);
        cout << "Ошибка! Сумма должна быть больше нуля.\n";
        setColor(7);
    }
}

static bool isIdUsed(const vector<unique_ptr<BankOperation> >& ops, int candidateId) {
    if (candidateId <= 0) return true;
    for (size_t i = 0; i < ops.size(); i++) {
        if (ops[i] != nullptr && ops[i]->getId() == candidateId) {
            return true;
        }
    }
    return false;
}

static bool isValidDateFormat(const string& date) {
    if (date.length() != 10 || date[2] != '.' || date[5] != '.') return false;
    for (size_t i = 0; i < date.length(); i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(static_cast<unsigned char>(date[i]))) return false;
    }
    int day = atoi(date.substr(0, 2).c_str());
    int month = atoi(date.substr(3, 2).c_str());
    int year = atoi(date.substr(6, 4).c_str());
    return (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1990 && year <= 2026);
}

static bool parseIntStrict(const string& s, int& outVal) {
    if (s.empty()) return false;
    stringstream ss(s);
    int v = 0;
    char extra = '\0';
    if (!(ss >> v) || (ss >> extra)) return false;
    outVal = v;
    return true;
}

static bool parseDoubleStrict(const string& s, double& outVal) {
    if (s.empty()) return false;
    stringstream ss(s);
    double v = 0.0;
    char extra = '\0';
    if (!(ss >> v) || (ss >> extra)) return false;
    outVal = v;
    return true;
}

static string sanitizeField(const string& s) {
    string res = s;
    for (size_t i = 0; i < res.length(); i++) {
        if (res[i] == '|' || res[i] == '\n' || res[i] == '\r') {
            res[i] = ' ';
        }
    }
    return res;
}

// ПАТТЕРН 1: ФАБРИЧНЫЙ МЕТОД - реализации виртуального метода без аргументов 
unique_ptr<BankOperation> DepositCreator::createOperation() const {
    return unique_ptr<BankOperation>(new DepositOperation());
}

unique_ptr<BankOperation> WithdrawalCreator::createOperation() const {
    return unique_ptr<BankOperation>(new WithdrawalOperation());
}

unique_ptr<BankOperation> TransferCreator::createOperation() const {
    return unique_ptr<BankOperation>(new TransferOperation());
}

unique_ptr<BankOperation> UtilityPaymentCreator::createOperation() const {
    return unique_ptr<BankOperation>(new UtilityPaymentOperation());
}

unique_ptr<BankOperation> CurrencyExchangeCreator::createOperation() const {
    return unique_ptr<BankOperation>(new CurrencyExchangeOperation());
}

// Реализация документов
DepositReceipt::DepositReceipt(int id, const string& d, double amt, const string& acc, const string& src)
    : operationId(id), date(d), amount(amt), accountNumber(acc), source(src) {
}

void DepositReceipt::printDocument(ostream& os) const {
    os << "Документ: " << getDocumentTitle() << " Операция #" << operationId
        << " от " << date << " | Счет: " << accountNumber
        << " | Сумма: " << amount << " | Источник: " << source;
}

string DepositReceipt::getDocumentTitle() const {
    return "Приходный кассовый ордер";
}

WithdrawalSlip::WithdrawalSlip(int id, const string& d, double amt, const string& acc, const string& atm)
    : operationId(id), date(d), amount(amt), accountNumber(acc), atmId(atm) {
}

void WithdrawalSlip::printDocument(ostream& os) const {
    os << "Документ: " << getDocumentTitle() << " Операция #" << operationId
        << " от " << date << " | Счет: " << accountNumber
        << " | Выдано: " << amount << " | Устройство/касса: " << atmId;
}

string WithdrawalSlip::getDocumentTitle() const {
    return "Расходный ордер на выдачу наличных";
}

TransferInvoice::TransferInvoice(int id, const string& d, double amt, const string& acc, const string& tgt)
    : operationId(id), date(d), amount(amt), accountNumber(acc), targetAccount(tgt) {
}

void TransferInvoice::printDocument(ostream& os) const {
    os << "Документ: " << getDocumentTitle() << " Операция #" << operationId
        << " от " << date << " | Со счета: " << accountNumber
        << " -> На счет: " << targetAccount << " | Сумма: " << amount;
}

string TransferInvoice::getDocumentTitle() const {
    return "Платежное поручение на перевод";
}

PaymentCheck::PaymentCheck(int id, const string& d, double amt, const string& acc, const string& prov)
    : operationId(id), date(d), amount(amt), accountNumber(acc), serviceProvider(prov) {
}

void PaymentCheck::printDocument(ostream& os) const {
    os << "Документ: " << getDocumentTitle() << " Операция #" << operationId
        << " от " << date << " | Счет плательщика: " << accountNumber
        << " | Получатель услуг: " << serviceProvider << " | Сумма: " << amount;
}

string PaymentCheck::getDocumentTitle() const {
    return "Квитанция об оплате услуги";
}

ExchangeCertificate::ExchangeCertificate(int id, const string& d, double amt, const string& acc, const string& curr, double rate)
    : operationId(id), date(d), amount(amt), accountNumber(acc), targetCurrency(curr), exchangeRate(rate) {
}

void ExchangeCertificate::printDocument(ostream& os) const {
    os << "Документ: " << getDocumentTitle() << " Операция #" << operationId
        << " от " << date << " | Счет: " << accountNumber
        << " | Сумма: " << amount << " -> Валюта: " << targetCurrency
        << " по курсу " << exchangeRate;
}

string ExchangeCertificate::getDocumentTitle() const {
    return "Справка о валютно-обменной операции";
}

// Реализация спецификаций для фабричного метода с аргументами
OperationSpec::OperationSpec(int opId, const string& opDate, double opAmount, const string& opAccount)
    : id(opId), date(opDate), amount(opAmount), accountNumber(opAccount) {
}

DepositSpec::DepositSpec(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opSource)
    : OperationSpec(opId, opDate, opAmount, opAccount), source(opSource) {
}
OperationType DepositSpec::getType() const { return OP_DEPOSIT; }

WithdrawalSpec::WithdrawalSpec(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opAtm)
    : OperationSpec(opId, opDate, opAmount, opAccount), atmId(opAtm) {
}
OperationType WithdrawalSpec::getType() const { return OP_WITHDRAWAL; }

TransferSpec::TransferSpec(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opTarget)
    : OperationSpec(opId, opDate, opAmount, opAccount), targetAccount(opTarget) {
}
OperationType TransferSpec::getType() const { return OP_TRANSFER; }

UtilityPaymentSpec::UtilityPaymentSpec(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opProvider)
    : OperationSpec(opId, opDate, opAmount, opAccount), serviceProvider(opProvider) {
}
OperationType UtilityPaymentSpec::getType() const { return OP_UTILITY; }

CurrencyExchangeSpec::CurrencyExchangeSpec(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opCurrency, double opRate)
    : OperationSpec(opId, opDate, opAmount, opAccount), targetCurrency(opCurrency), exchangeRate(opRate) {
}
OperationType CurrencyExchangeSpec::getType() const { return OP_EXCHANGE; }

// Реализация базового класса BankOperation
BankOperation::BankOperation()
    : id(0), date("01.01.2026"), amount(0.0), accountNumber("BY00BANK0000") {
}

BankOperation::BankOperation(int opId, const string& opDate, double opAmount, const string& opAccount)
    : id(opId), date(opDate), amount(opAmount), accountNumber(opAccount) {
}

int BankOperation::getId() const { return id; }
void BankOperation::setId(int newId) { id = newId; }
string BankOperation::getDate() const { return date; }
double BankOperation::getAmount() const { return amount; }
string BankOperation::getAccountNumber() const { return accountNumber; }

bool BankOperation::readCommonFields(istream& is) {
    string idStr;
    string d;
    string amtStr;
    string acc;

    if (!getline(is, idStr, '|')) return false;
    if (!getline(is, d, '|')) return false;
    if (!getline(is, amtStr, '|')) return false;
    if (!getline(is, acc, '|')) return false;

    int parsedId = 0;
    double parsedAmt = 0.0;
    if (!parseIntStrict(idStr, parsedId)) return false;
    if (!isValidDateFormat(d)) return false;
    if (!parseDoubleStrict(amtStr, parsedAmt) || parsedAmt <= 0.0) return false;
    if (acc.empty()) return false;

    id = parsedId;
    date = d;
    amount = parsedAmt;
    accountNumber = acc;
    return true;
}

ostream& operator<<(ostream& os, const BankOperation& op) {
    os << "ID: " << op.id
        << " | Тип: " << op.getTypeName()
        << " | Дата: " << op.date
        << " | Сумма: " << op.amount
        << " | Счет: " << op.accountNumber;
    op.printDetails(os);
    return os;
}

istream& operator>>(istream& is, BankOperation& op) {
    if (!op.readFromStream(is)) {
        is.setstate(ios::failbit);
    }
    return is;
}

// ПАТТЕРН 2: ФАБРИЧНЫЙ МЕТОД С АРГУМЕНТАМИ
unique_ptr<BankOperation> BankOperation::createWithArgs(const OperationSpec* spec) {
    if (spec == nullptr) return unique_ptr<BankOperation>();
    switch (spec->getType()) {
    case OP_DEPOSIT: {
        const DepositSpec* dSpec = static_cast<const DepositSpec*>(spec);
        return unique_ptr<BankOperation>(new DepositOperation(dSpec->id, dSpec->date, dSpec->amount, dSpec->accountNumber, dSpec->source));
    }
    case OP_WITHDRAWAL: {
        const WithdrawalSpec* wSpec = static_cast<const WithdrawalSpec*>(spec);
        return unique_ptr<BankOperation>(new WithdrawalOperation(wSpec->id, wSpec->date, wSpec->amount, wSpec->accountNumber, wSpec->atmId));
    }
    case OP_TRANSFER: {
        const TransferSpec* tSpec = static_cast<const TransferSpec*>(spec);
        return unique_ptr<BankOperation>(new TransferOperation(tSpec->id, tSpec->date, tSpec->amount, tSpec->accountNumber, tSpec->targetAccount));
    }
    case OP_UTILITY: {
        const UtilityPaymentSpec* uSpec = static_cast<const UtilityPaymentSpec*>(spec);
        return unique_ptr<BankOperation>(new UtilityPaymentOperation(uSpec->id, uSpec->date, uSpec->amount, uSpec->accountNumber, uSpec->serviceProvider));
    }
    case OP_EXCHANGE: {
        const CurrencyExchangeSpec* eSpec = static_cast<const CurrencyExchangeSpec*>(spec);
        return unique_ptr<BankOperation>(new CurrencyExchangeOperation(eSpec->id, eSpec->date, eSpec->amount, eSpec->accountNumber, eSpec->targetCurrency, eSpec->exchangeRate));
    }
    default:
        return unique_ptr<BankOperation>();
    }
}

// ПАТТЕРН 3: ФАБРИЧНЫЙ КОНСТРУКТОР
void BankOperation::registerCreator(OperationFactoryFunc creatorFunc) {
    int assignedId = static_cast<int>(operationRegistry.size());
    operationRegistry.push_back(make_pair(assignedId, creatorFunc));
}

unique_ptr<BankOperation> BankOperation::createFromRegistry(int registryIndex, int newId) {
    if (registryIndex < 0 || static_cast<size_t>(registryIndex) >= operationRegistry.size()) {
        return unique_ptr<BankOperation>();
    }
    OperationFactoryFunc creatorFunc = operationRegistry[static_cast<size_t>(registryIndex)].second;
    if (creatorFunc == nullptr) return unique_ptr<BankOperation>();
    unique_ptr<BankOperation> obj = creatorFunc();
    if (obj != nullptr) {
        obj->setId(newId);
    }
    return obj;
}

size_t BankOperation::getRegistrySize() {
    return operationRegistry.size();
}

// DepositOperation 
DepositOperation::DepositOperation()
    : ClonableOperation<DepositOperation>(), source("Касса банка") {}

DepositOperation::DepositOperation(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opSource)
    : ClonableOperation<DepositOperation>(opId, opDate, opAmount, opAccount), source(opSource) {}

OperationType DepositOperation::getOperationType() const { return OP_DEPOSIT; }
string DepositOperation::getTypeName() const { return "Пополнение счета"; }

void DepositOperation::inputFields(int newId) {
    id = newId;
    date = inputDateString("Введите дату операции (ДД.ММ.ГГГГ): ");
    amount = inputPositiveAmount("Введите сумму пополнения: ");
    accountNumber = inputAlphanumericString("Введите номер счета: ");
    source = inputString("Введите источник пополнения (буквы и пробелы): ");
}

void DepositOperation::edit() {
    date = inputDateString("Новая дата (ДД.ММ.ГГГГ): ");
    amount = inputPositiveAmount("Новая сумма пополнения: ");
    accountNumber = inputAlphanumericString("Новый номер счета: ");
    source = inputString("Новый источник пополнения: ");
}

void DepositOperation::printDetails(ostream& os) const {
    os << " | Источник: " << source;
}

void DepositOperation::writeRecord(ostream& os) const {
    os << "OP|" << static_cast<int>(OP_DEPOSIT) << "|" << id << "|" << sanitizeField(date)
        << "|" << amount << "|" << sanitizeField(accountNumber) << "|" << sanitizeField(source) << "\n";
}

bool DepositOperation::readFromStream(istream& is) {
    if (!readCommonFields(is)) return false;
    string src;
    if (!getline(is, src)) return false;
    if (src.empty()) return false;
    source = src;
    return true;
}

unique_ptr<BankOperation> DepositOperation::createInstance() { return unique_ptr<BankOperation>(new DepositOperation()); }
void DepositOperation::Register() { BankOperation::registerCreator(&DepositOperation::createInstance); }

unique_ptr<OperationDocument> DepositOperation::createDocument() const {
    return unique_ptr<OperationDocument>(new DepositReceipt(id, date, amount, accountNumber, source));
}

// WithdrawalOperation
WithdrawalOperation::WithdrawalOperation()
    : ClonableOperation<WithdrawalOperation>(), atmId("Банкомат-101") {}

WithdrawalOperation::WithdrawalOperation(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opAtm)
    : ClonableOperation<WithdrawalOperation>(opId, opDate, opAmount, opAccount), atmId(opAtm) {}

OperationType WithdrawalOperation::getOperationType() const { return OP_WITHDRAWAL; }
string WithdrawalOperation::getTypeName() const { return "Снятие наличных"; }

void WithdrawalOperation::inputFields(int newId) {
    id = newId;
    date = inputDateString("Введите дату операции (ДД.ММ.ГГГГ): ");
    amount = inputPositiveAmount("Введите сумму снятия: ");
    accountNumber = inputAlphanumericString("Введите номер счета: ");
    atmId = inputAlphanumericString("Введите код банкомата: ");
}

void WithdrawalOperation::edit() {
    date = inputDateString("Новая дата (ДД.ММ.ГГГГ): ");
    amount = inputPositiveAmount("Новая сумма снятия: ");
    accountNumber = inputAlphanumericString("Новый номер счета: ");
    atmId = inputAlphanumericString("Новый код банкомата: ");
}

void WithdrawalOperation::printDetails(ostream& os) const {
    os << " | Банкомат/касса: " << atmId;
}

void WithdrawalOperation::writeRecord(ostream& os) const {
    os << "OP|" << static_cast<int>(OP_WITHDRAWAL) << "|" << id << "|" << sanitizeField(date)
        << "|" << amount << "|" << sanitizeField(accountNumber) << "|" << sanitizeField(atmId) << "\n";
}

bool WithdrawalOperation::readFromStream(istream& is) {
    if (!readCommonFields(is)) return false;
    string atm;
    if (!getline(is, atm)) return false;
    if (atm.empty()) return false;
    atmId = atm;
    return true;
}

unique_ptr<BankOperation> WithdrawalOperation::createInstance() { return unique_ptr<BankOperation>(new WithdrawalOperation()); }
void WithdrawalOperation::Register() { BankOperation::registerCreator(&WithdrawalOperation::createInstance); }

unique_ptr<OperationDocument> WithdrawalOperation::createDocument() const {
    return unique_ptr<OperationDocument>(new WithdrawalSlip(id, date, amount, accountNumber, atmId));
}

// TransferOperation
TransferOperation::TransferOperation()
    : ClonableOperation<TransferOperation>(), targetAccount("BY00BANK9999") {}

TransferOperation::TransferOperation(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opTarget)
    : ClonableOperation<TransferOperation>(opId, opDate, opAmount, opAccount), targetAccount(opTarget) {}

OperationType TransferOperation::getOperationType() const { return OP_TRANSFER; }
string TransferOperation::getTypeName() const { return "Перевод между счетами"; }

void TransferOperation::inputFields(int newId) {
    id = newId;
    date = inputDateString("Введите дату операции (ДД.ММ.ГГГГ): ");
    amount = inputPositiveAmount("Введите сумму перевода: ");
    accountNumber = inputAlphanumericString("Введите счет списания: ");
    targetAccount = inputAlphanumericString("Введите счет получателя: ");
}

void TransferOperation::edit() {
    date = inputDateString("Новая дата (ДД.ММ.ГГГГ): ");
    amount = inputPositiveAmount("Новая сумма перевода: ");
    accountNumber = inputAlphanumericString("Новый счет списания: ");
    targetAccount = inputAlphanumericString("Новый счет получателя: ");
}

void TransferOperation::printDetails(ostream& os) const {
    os << " | Счет получателя: " << targetAccount;
}

void TransferOperation::writeRecord(ostream& os) const {
    os << "OP|" << static_cast<int>(OP_TRANSFER) << "|" << id << "|" << sanitizeField(date)
        << "|" << amount << "|" << sanitizeField(accountNumber) << "|" << sanitizeField(targetAccount) << "\n";
}

bool TransferOperation::readFromStream(istream& is) {
    if (!readCommonFields(is)) return false;
    string tgt;
    if (!getline(is, tgt)) return false;
    if (tgt.empty()) return false;
    targetAccount = tgt;
    return true;
}

unique_ptr<BankOperation> TransferOperation::createInstance() { return unique_ptr<BankOperation>(new TransferOperation()); }
void TransferOperation::Register() { BankOperation::registerCreator(&TransferOperation::createInstance); }

unique_ptr<OperationDocument> TransferOperation::createDocument() const {
    return unique_ptr<OperationDocument>(new TransferInvoice(id, date, amount, accountNumber, targetAccount));
}

// UtilityPaymentOperation
UtilityPaymentOperation::UtilityPaymentOperation()
    : ClonableOperation<UtilityPaymentOperation>(), serviceProvider("Коммунальные службы") {}

UtilityPaymentOperation::UtilityPaymentOperation(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opProvider)
    : ClonableOperation<UtilityPaymentOperation>(opId, opDate, opAmount, opAccount), serviceProvider(opProvider) {}

OperationType UtilityPaymentOperation::getOperationType() const { return OP_UTILITY; }
string UtilityPaymentOperation::getTypeName() const { return "Оплата услуг"; }

void UtilityPaymentOperation::inputFields(int newId) {
    id = newId;
    date = inputDateString("Введите дату операции (ДД.ММ.ГГГГ): ");
    amount = inputPositiveAmount("Введите сумму оплаты: ");
    accountNumber = inputAlphanumericString("Введите номер счета: ");
    serviceProvider = inputString("Введите поставщика услуг (буквы и пробелы): ");
}

void UtilityPaymentOperation::edit() {
    date = inputDateString("Новая дата (ДД.ММ.ГГГГ): ");
    amount = inputPositiveAmount("Новая сумма оплаты: ");
    accountNumber = inputAlphanumericString("Новый номер счета: ");
    serviceProvider = inputString("Новый поставщик услуг: ");
}

void UtilityPaymentOperation::printDetails(ostream& os) const {
    os << " | Поставщик услуг: " << serviceProvider;
}

void UtilityPaymentOperation::writeRecord(ostream& os) const {
    os << "OP|" << static_cast<int>(OP_UTILITY) << "|" << id << "|" << sanitizeField(date)
        << "|" << amount << "|" << sanitizeField(accountNumber) << "|" << sanitizeField(serviceProvider) << "\n";
}

bool UtilityPaymentOperation::readFromStream(istream& is) {
    if (!readCommonFields(is)) return false;
    string prov;
    if (!getline(is, prov)) return false;
    if (prov.empty()) return false;
    serviceProvider = prov;
    return true;
}

unique_ptr<BankOperation> UtilityPaymentOperation::createInstance() { return unique_ptr<BankOperation>(new UtilityPaymentOperation()); }
void UtilityPaymentOperation::Register() { BankOperation::registerCreator(&UtilityPaymentOperation::createInstance); }

unique_ptr<OperationDocument> UtilityPaymentOperation::createDocument() const {
    return unique_ptr<OperationDocument>(new PaymentCheck(id, date, amount, accountNumber, serviceProvider));
}

// CurrencyExchangeOperation 
CurrencyExchangeOperation::CurrencyExchangeOperation()
    : ClonableOperation<CurrencyExchangeOperation>(), targetCurrency("USD"), exchangeRate(3.25) {}

CurrencyExchangeOperation::CurrencyExchangeOperation(int opId, const string& opDate, double opAmount, const string& opAccount, const string& opCurrency, double opRate)
    : ClonableOperation<CurrencyExchangeOperation>(opId, opDate, opAmount, opAccount), targetCurrency(opCurrency), exchangeRate(opRate) {}

OperationType CurrencyExchangeOperation::getOperationType() const { return OP_EXCHANGE; }
string CurrencyExchangeOperation::getTypeName() const { return "Обмен валют"; }

void CurrencyExchangeOperation::inputFields(int newId) {
    id = newId;
    date = inputDateString("Введите дату операции (ДД.ММ.ГГГГ): ");
    amount = inputPositiveAmount("Введите сумму в базовой валюте: ");
    accountNumber = inputAlphanumericString("Введите номер счета: ");
    targetCurrency = inputString("Введите целевую валюту (буквы): ");
    while (true) {
        exchangeRate = inputDouble("Введите курс обмена: ");
        if (exchangeRate > 0.0) break;
        setColor(12);
        cout << "Ошибка! Курс обмена должен быть больше нуля.\n";
        setColor(7);
    }
}

void CurrencyExchangeOperation::edit() {
    date = inputDateString("Новая дата (ДД.ММ.ГГГГ): ");
    amount = inputPositiveAmount("Новая сумма: ");
    accountNumber = inputAlphanumericString("Новый номер счета: ");
    targetCurrency = inputString("Новая целевая валюта: ");
    while (true) {
        exchangeRate = inputDouble("Новый курс обмена: ");
        if (exchangeRate > 0.0) break;
        setColor(12);
        cout << "Ошибка! Курс обмена должен быть больше нуля.\n";
        setColor(7);
    }
}

void CurrencyExchangeOperation::printDetails(ostream& os) const {
    os << " | Валюта: " << targetCurrency << " | Курс: " << exchangeRate;
}

void CurrencyExchangeOperation::writeRecord(ostream& os) const {
    os << "OP|" << static_cast<int>(OP_EXCHANGE) << "|" << id << "|" << sanitizeField(date)
        << "|" << amount << "|" << sanitizeField(accountNumber) << "|" << sanitizeField(targetCurrency)
        << "|" << exchangeRate << "\n";
}

bool CurrencyExchangeOperation::readFromStream(istream& is) {
    if (!readCommonFields(is)) return false;
    string curr;
    string rateStr;
    if (!getline(is, curr, '|')) return false;
    if (!getline(is, rateStr)) return false;
    double parsedRate = 0.0;
    if (curr.empty() || !parseDoubleStrict(rateStr, parsedRate) || parsedRate <= 0.0) return false;
    targetCurrency = curr;
    exchangeRate = parsedRate;
    return true;
}

unique_ptr<BankOperation> CurrencyExchangeOperation::createInstance() { return unique_ptr<BankOperation>(new CurrencyExchangeOperation()); }
void CurrencyExchangeOperation::Register() { BankOperation::registerCreator(&CurrencyExchangeOperation::createInstance); }

unique_ptr<OperationDocument> CurrencyExchangeOperation::createDocument() const {
    return unique_ptr<OperationDocument>(new ExchangeCertificate(id, date, amount, accountNumber, targetCurrency, exchangeRate));
}

// --- Работа с коллекцией операций ---
// ПАТТЕРН 1: ФАБРИЧНЫЙ МЕТОД - выбор конкретного создателя из иерархии OperationCreator
static unique_ptr<OperationCreator> askOperationCreator() {
    while (true) {
        setColor(11);
        cout << "\n--- Выбор банковской операции ---\n";
        setColor(7);
        cout << "1. Пополнение счета\n";
        cout << "2. Снятие наличных\n";
        cout << "3. Перевод между счетами\n";
        cout << "4. Оплата услуг\n";
        cout << "5. Обмен валют\n";
        int choice = inputInt("Ваш выбор (1-5): ");
        if (choice == 1) return unique_ptr<OperationCreator>(new DepositCreator());
        if (choice == 2) return unique_ptr<OperationCreator>(new WithdrawalCreator());
        if (choice == 3) return unique_ptr<OperationCreator>(new TransferCreator());
        if (choice == 4) return unique_ptr<OperationCreator>(new UtilityPaymentCreator());
        if (choice == 5) return unique_ptr<OperationCreator>(new CurrencyExchangeCreator());
        setColor(12);
        cout << "Ошибка! Выберите пункт от 1 до 5.\n";
        setColor(7);
    }
}

static OperationType askOperationType() {
    while (true) {
        setColor(11);
        cout << "\n--- Выбор типа банковской операции ---\n";
        setColor(7);
        cout << "1. Пополнение счета\n";
        cout << "2. Снятие наличных\n";
        cout << "3. Перевод между счетами\n";
        cout << "4. Оплата услуг\n";
        cout << "5. Обмен валют\n";
        int choice = inputInt("Ваш выбор (1-5): ");
        if (choice >= 1 && choice <= 5) {
            return static_cast<OperationType>(choice);
        }
        setColor(12);
        cout << "Ошибка! Выберите пункт от 1 до 5.\n";
        setColor(7);
    }
}

void addOperationMenu(vector<unique_ptr<BankOperation> >& ops) {
    while (true) {
        setColor(14);
        cout << "\n--- Режим оформления банковской операции ---\n";
        setColor(7);
        cout << "1. Оформить операцию с пошаговым вводом реквизитов\n";
        cout << "2. Оформить операцию единым пакетом данных\n";
        cout << "3. Оформить операцию по коду категории\n";
        cout << "4. Оформить операцию и сразу вывести документ\n";
        cout << "5. Оформить операцию на основе шаблона из существующей\n";
        int patternChoice = inputInt("Выберите режим оформления (1-5): ");

        if (patternChoice < 1 || patternChoice > 5) {
            setColor(12);
            cout << "Ошибка! Введите число от 1 до 5.\n";
            setColor(7);
            continue;
        }

        int newId = generateUniqueOperationId(ops);

        if (patternChoice == 1) {
            // ПАТТЕРН 1: ФАБРИЧНЫЙ МЕТОД
            unique_ptr<OperationCreator> creator = askOperationCreator();
            unique_ptr<BankOperation> obj = creator->createOperation();
            obj->inputFields(newId);
            ops.push_back(std::move(obj));
            setColor(10);
            cout << "Операция оформлена. Присвоен ID: " << newId << "\n";
            setColor(7);
            return;
        }
        else if (patternChoice == 2) {
            // ПАТТЕРН 2: ФАБРИЧНЫЙ МЕТОД С АРГУМЕНТАМИ
            OperationType opType = askOperationType();
            string d = inputDateString("Введите дату (ДД.ММ.ГГГГ): ");
            double amt = inputPositiveAmount("Введите сумму: ");
            string acc = inputAlphanumericString("Введите номер счета: ");

            unique_ptr<OperationSpec> spec;
            if (opType == OP_DEPOSIT) {
                string src = inputString("Источник пополнения: ");
                spec.reset(new DepositSpec(newId, d, amt, acc, src));
            }
            else if (opType == OP_WITHDRAWAL) {
                string atm = inputAlphanumericString("Код банкомата: ");
                spec.reset(new WithdrawalSpec(newId, d, amt, acc, atm));
            }
            else if (opType == OP_TRANSFER) {
                string tgt = inputAlphanumericString("Счет получателя: ");
                spec.reset(new TransferSpec(newId, d, amt, acc, tgt));
            }
            else if (opType == OP_UTILITY) {
                string prov = inputString("Поставщик услуг: ");
                spec.reset(new UtilityPaymentSpec(newId, d, amt, acc, prov));
            }
            else if (opType == OP_EXCHANGE) {
                string curr = inputString("Целевая валюта: ");
                double rate = 0.0;
                while (true) {
                    rate = inputDouble("Курс обмена: ");
                    if (rate > 0.0) break;
                    setColor(12);
                    cout << "Ошибка! Курс должен быть больше нуля.\n";
                    setColor(7);
                }
                spec.reset(new CurrencyExchangeSpec(newId, d, amt, acc, curr, rate));
            }

            unique_ptr<BankOperation> obj = BankOperation::createWithArgs(spec.get());
            if (obj != nullptr) {
                ops.push_back(std::move(obj));
                setColor(10);
                cout << "Операция оформлена по введенным данным. ID: " << newId << "\n";
                setColor(7);
            }
            return;
        }
        else if (patternChoice == 3) {
            // ПАТТЕРН 3: ФАБРИЧНЫЙ КОНСТРУКТОР
            int regCount = static_cast<int>(BankOperation::getRegistrySize());
            cout << "Доступно типов операций в системе: " << regCount << "\n";
            cout << "0 - Пополнение счета\n1 - Снятие наличных\n2 - Перевод между счетами\n3 - Оплата услуг\n4 - Обмен валют\n";
            int regIdx = inputInt("Введите номер типа операции (0..4): ");
            unique_ptr<BankOperation> obj = BankOperation::createFromRegistry(regIdx, newId);
            if (obj == nullptr) {
                setColor(12);
                cout << "Ошибка! Неверный номер типа операции.\n";
                setColor(7);
                continue;
            }
            obj->inputFields(newId);
            ops.push_back(std::move(obj));
            setColor(10);
            cout << "Операция оформлена. ID: " << newId << "\n";
            setColor(7);
            return;
        }
        else if (patternChoice == 4) {
            // ПАТТЕРН 4: ПОЛИМОРФНАЯ ФАБРИКА
            unique_ptr<OperationCreator> creator = askOperationCreator();
            unique_ptr<BankOperation> obj = creator->createOperation();
            obj->inputFields(newId);

            unique_ptr<OperationDocument> doc = obj->createDocument();
            setColor(10);
            cout << "Операция оформлена. Сформирован документ:\n";
            setColor(13);
            if (doc != nullptr) {
                doc->printDocument(cout);
            }
            cout << "\n";
            setColor(7);
            ops.push_back(std::move(obj));
            return;
        }
        else if (patternChoice == 5) {
            // ПАТТЕРН 5: ПОЛИМОРФНОЕ КОПИРОВАНИЕ
            if (ops.empty()) {
                setColor(12);
                cout << "Список операций пуст. Сначала добавьте хотя бы одну операцию.\n";
                setColor(7);
                return;
            }
            displayAllOperations(ops);
            int targetId = inputInt("Введите ID операции для копирования: ");
            const BankOperation* found = nullptr;
            for (size_t i = 0; i < ops.size(); i++) {
                if (ops[i] != nullptr && ops[i]->getId() == targetId) {
                    found = ops[i].get();
                    break;
                }
            }
            if (found == nullptr) {
                setColor(12);
                cout << "Операция с ID " << targetId << " не найдена.\n";
                setColor(7);
                continue;
            }
            unique_ptr<BankOperation> copyObj = found->clone();
            if (copyObj != nullptr) {
                copyObj->setId(newId);
                ops.push_back(std::move(copyObj));
                setColor(10);
                cout << "Создана копия операции #" << targetId << " с новым ID: " << newId << "\n";
                setColor(7);
            }
            return;
        }
    }
}

void deleteOperationById(vector<unique_ptr<BankOperation> >& ops) {
    if (ops.empty()) {
        setColor(12);
        cout << "Список операций пуст.\n";
        setColor(7);
        return;
    }
    int targetId = inputInt("Введите ID операции для удаления: ");
    for (size_t i = 0; i < ops.size(); i++) {
        if (ops[i] != nullptr && ops[i]->getId() == targetId) {
            ops.erase(ops.begin() + static_cast<ptrdiff_t>(i));
            setColor(10);
            cout << "Операция с ID " << targetId << " успешно удалена.\n";
            setColor(7);
            return;
        }
    }
    setColor(12);
    cout << "Операция с ID " << targetId << " не найдена.\n";
    setColor(7);
}

void editOperationById(vector<unique_ptr<BankOperation> >& ops) {
    if (ops.empty()) {
        setColor(12);
        cout << "Список операций пуст.\n";
        setColor(7);
        return;
    }
    int targetId = inputInt("Введите ID операции для редактирования: ");
    for (size_t i = 0; i < ops.size(); i++) {
        if (ops[i] != nullptr && ops[i]->getId() == targetId) {
            setColor(11);
            cout << "Текущие данные: " << (*ops[i]) << "\n";
            setColor(7);
            ops[i]->edit();
            setColor(10);
            cout << "Данные операции обновлены.\n";
            setColor(7);
            return;
        }
    }
    setColor(12);
    cout << "Операция с ID " << targetId << " не найдена.\n";
    setColor(7);
}

void displayAllOperations(const vector<unique_ptr<BankOperation> >& ops) {
    if (ops.empty()) {
        setColor(12);
        cout << "Список банковских операций пуст.\n";
        setColor(7);
        return;
    }
    setColor(11);
    cout << "\n=== СПИСОК БАНКОВСКИХ ОПЕРАЦИЙ (" << ops.size() << ") ===\n";
    setColor(7);
    for (size_t i = 0; i < ops.size(); i++) {
        if (ops[i] != nullptr) {
            cout << (i + 1) << ". " << (*ops[i]) << "\n";
            unique_ptr<OperationDocument> doc = ops[i]->createDocument();
            if (doc != nullptr) {
                setColor(8);
                cout << "   ";
                doc->printDocument(cout);
                cout << "\n";
                setColor(7);
            }
        }
    }
}

void saveOperationsToFile(const vector<unique_ptr<BankOperation> >& ops, const string& filename) {
    ofstream ofs(filename.c_str());
    if (!ofs.is_open()) {
        setColor(12);
        cout << "Ошибка открытия файла для записи: " << filename << "\n";
        setColor(7);
        return;
    }
    ofs << "=== ОТЧЕТ ПО БАНКОВСКИМ ОПЕРАЦИЯМ ===\n";
    ofs << "Всего операций: " << ops.size() << "\n\n";
    for (size_t i = 0; i < ops.size(); i++) {
        if (ops[i] != nullptr) {
            ops[i]->writeRecord(ofs);
            ofs << "   " << (*ops[i]) << "\n";
            unique_ptr<OperationDocument> doc = ops[i]->createDocument();
            if (doc != nullptr) {
                ofs << "   ";
                doc->printDocument(ofs);
                ofs << "\n";
            }
        }
    }
    ofs.close();
    setColor(10);
    cout << "Данные успешно сохранены в файл: " << filename << "\n";
    setColor(7);
}

void loadOperationsFromFile(vector<unique_ptr<BankOperation> >& ops, const string& filename) {
    ifstream ifs(filename.c_str());
    if (!ifs.is_open()) {
        setColor(12);
        cout << "Ошибка открытия файла для чтения: " << filename << "\n";
        setColor(7);
        return;
    }

    string line;
    int loadedCount = 0;
    int skippedCount = 0;

    while (getline(ifs, line)) {
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }
        if (line.empty()) continue;

        stringstream lineStream(line);
        string prefix;
        string typeStr;
        if (!getline(lineStream, prefix, '|') || prefix != "OP") {
            continue;
        }
        if (!getline(lineStream, typeStr, '|')) {
            skippedCount++;
            continue;
        }

        int typeCode = 0;
        if (!parseIntStrict(typeStr, typeCode)) {
            skippedCount++;
            continue;
        }

        // ПАТТЕРН 3: ФАБРИЧНЫЙ КОНСТРУКТОР - создаем пустой объект по индексу в реестре (0..4)
        int registryIndex = typeCode - 1;
        unique_ptr<BankOperation> restored = BankOperation::createFromRegistry(registryIndex, 0);
        if (restored == nullptr) {
            skippedCount++;
            continue;
        }

        if (!(lineStream >> (*restored))) {
            skippedCount++;
            continue;
        }

        if (isIdUsed(ops, restored->getId())) {
            restored->setId(generateUniqueOperationId(ops));
        }

        ops.push_back(std::move(restored));
        loadedCount++;
    }

    ifs.close();
    setColor(10);
    cout << "Загружено операций из файла '" << filename << "': " << loadedCount << "\n";
    setColor(7);
    if (skippedCount > 0) {
        setColor(14);
        cout << "Пропущено некорректных строк: " << skippedCount << "\n";
        setColor(7);
    }
}