#include<iostream>
#include "converter.h"

using namespace std;

int inputInt(const char* msg) {
    int v;
    while (true) {
        cout << msg;

        if (cin >> v) {
            if (cin.peek() != '\n' && cin.peek() != ' ' && !cin.eof()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка! Введите целое число!\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        else {
            cout << "Ошибка! Введите целое число!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return v;
}

double inputDouble(const char* msg) {
    double v;
    while (true) {
        cout << msg;

        if (cin >> v) {
            if (cin.peek() != '\n' && cin.peek() != ' ' && !cin.eof()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка! Введите число!\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        else {
            cout << "Ошибка! Введите число!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return v;
}

void inputString(char* buffer, int maxLen, const char* msg) {
    while (true) {
        cout << msg;

        if (!cin.getline(buffer, maxLen)) {
            cin.clear();
            continue;
        }

        if (buffer[0] == '\0') {
            cout << "Ошибка! Строка не может быть пустой.\n";
            continue;
        }

        bool ok = true;
        for (int i = 0; buffer[i] != '\0'; i++) {
            unsigned char c = (unsigned char)buffer[i];
            if (c < 128 && !isalpha(c) && c != ' ')
                ok = false;
        }

        if (ok) break;
        cout << "Ошибка! Допускаются только буквы и пробелы.\n";
    }
}


User::User() : id(0) {
    name[0] = '\0';
}

User::User(int id, const char* n) : id(id) {
    strncpy_s(name, sizeof(name), n, sizeof(name) - 1);
}

User::User(const User& other) : id(other.id) {
    strncpy_s(name, sizeof(name), other.name, sizeof(name) - 1);
}

User::~User() {}

void User::setId(int id) { 
    this->id = id; 
}
int User::getId() const { 
    return id; 
}

void User::setName(const char* n) {
    strncpy_s(name, sizeof(name), n, sizeof(name) - 1);
}

const char* User::getName() const { 
    return name; 
}



FileFormat::FileFormat() {
    ext[0] = '\0';
}

FileFormat::FileFormat(const char* e) {
    strncpy_s(ext, sizeof(ext), e, sizeof(ext) - 1);
}

FileFormat::FileFormat(const FileFormat& other) {
    strncpy_s(ext, sizeof(ext), other.ext, sizeof(ext) - 1);
}

FileFormat::~FileFormat() {}

void FileFormat::setExt(const char* e) {
    strncpy_s(ext, sizeof(ext), e, sizeof(ext) - 1);
}

const char* FileFormat::getExt() const { 
    return ext;
}


ConversionRecord::ConversionRecord() : userId(0), success(false)
{
    fromExt[0] = '\0';
    toExt[0] = '\0';
}

ConversionRecord::ConversionRecord(int userId, const char* fromE, const char* toE, bool success)
    : userId(userId), success(success)
{
    strncpy_s(fromExt, sizeof(fromExt), fromE, sizeof(fromExt) - 1);
    strncpy_s(toExt, sizeof(toExt), toE, sizeof(toExt) - 1);
}

ConversionRecord::ConversionRecord(const ConversionRecord& other)
    : userId(other.userId), success(other.success)
{
    strncpy_s(fromExt, sizeof(fromExt), other.fromExt, sizeof(fromExt) - 1);
    strncpy_s(toExt, sizeof(toExt), other.toExt, sizeof(other.toExt) - 1);
}

ConversionRecord::~ConversionRecord() {}

void ConversionRecord::setUserId(int id) { 
    userId = id; 
}
int ConversionRecord::getUserId() const { 
    return userId; 
}

void ConversionRecord::setFromExt(const char* e) {
    strncpy_s(fromExt, sizeof(fromExt), e, sizeof(fromExt) - 1);
}

const char* ConversionRecord::getFromExt() const { 
    return fromExt;
}

void ConversionRecord::setToExt(const char* e) {
    strncpy_s(toExt, sizeof(toExt), e, sizeof(toExt) - 1);
}

const char* ConversionRecord::getToExt() const { 
    return toExt; 
}

void ConversionRecord::setSuccess(bool s) { 
    success = s; 
}
bool ConversionRecord::isSuccess() const { 
    return success; 
}


ConverterSystem::ConverterSystem() : userCount(0), recordCount(0) {
}

ConverterSystem::ConverterSystem(const ConverterSystem& other)
    : userCount(other.userCount), recordCount(other.recordCount)
{
    for (int i = 0; i < userCount; i++) {
        users[i] = other.users[i];
    }

    for (int i = 0; i < recordCount; i++) {
        records[i] = other.records[i];
    }
}

ConverterSystem::~ConverterSystem() {}

void ConverterSystem::addUser() {
    if (userCount >= MAX_USERS) {
        cout << "Максимум пользователей достигнут.\n";
        return;
    }

    int id = inputInt("Введите ID пользователя: ");

    for (int i = 0; i < userCount; i++) {
        if (users[i].getId() == id) {
            cout << "Пользователь с таким ID уже существует.\n";
            return;
        }
    }

    char name[64];
    inputString(name, 64, "Введите имя пользователя: ");

    users[userCount] = User(id, name);
    userCount++;

    cout << "Пользователь добавлен.\n";
}

User* ConverterSystem::findUserById(int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].getId() == id)
            return &users[i];
    }
    return nullptr;
}

void ConverterSystem::doConversion() {
    if (userCount == 0) {
        cout << "Нет пользователей.\n";
        return;
    }

    int userId = inputInt("Введите ID пользователя: ");
    User* u = findUserById(userId);
    if (!u) {
        cout << "Пользователь не найден.\n";
        return;
    }

    char fromExt[16], toExt[16];

    cout << "Введите исходный формат: ";
    cin.getline(fromExt, 16);

    cout << "Введите конечный формат: ";
    cin.getline(toExt, 16);

    double inSize = inputDouble("Введите условный размер файла: ");
    double outSize = 0;

    Converter<double> conv;
    bool ok = conv.convert(inSize, outSize);

    if (strcmp(fromExt, toExt) == 0)
        ok = false;

    records[recordCount++] = ConversionRecord(userId, fromExt, toExt, ok);

    cout << (ok ? "Конвертация успешна.\n" : "Ошибка конвертации.\n");
}

void ConverterSystem::showLogsByUser() {
    int id = inputInt("Введите ID пользователя: ");
    bool found = false;

    for (int i = 0; i < recordCount; i++) {
        if (records[i].getUserId() == id) {
            found = true;
            cout << records[i].getFromExt() << " -> " << records[i].getToExt()
                << " : " << (records[i].isSuccess() ? "УСПЕХ" : "ОШИБКА") << "\n";
        }
    }

    if (!found) cout << "Нет записей.\n";
}

void ConverterSystem::showLogsByFormat() {
    char fmt[16];
    cout << "Введите формат: ";
    cin.getline(fmt, 16);

    bool found = false;

    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].getFromExt(), fmt) == 0) {
            found = true;
            cout << "User " << records[i].getUserId()
                << ": " << records[i].getFromExt() << " -> " << records[i].getToExt()
                << " : " << (records[i].isSuccess() ? "УСПЕХ" : "ОШИБКА") << "\n";
        }
    }

    if (!found) cout << "Нет записей.\n";
}