#include<iostream>
#include "converter.h"

using namespace std;

SmartPointer<Converter>* converters = NULL;
int convertersCount = 0;
int convertersMax = 0;

ConversionResult* logs = NULL;
int logsCount = 0;
int logsMax = 0;


void copyString(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (src[i] != '\0' && i < maxLen - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

bool equalString(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}


User::User() { name[0] = '\0'; }
User::User(const char* n) { setName(n); }
User::User(const User& u) { copyString(name, u.name, MAX_NAME); }
User::~User() {}

void User::setName(const char* n) { copyString(name, n, MAX_NAME); }
const char* User::getName() const { return name; }


FileFormat::FileFormat() { format[0] = '\0'; }
FileFormat::FileFormat(const char* f) { setFormat(f); }
FileFormat::FileFormat(const FileFormat& ff) { copyString(format, ff.format, MAX_FORMAT); }
FileFormat::~FileFormat() {}

void FileFormat::setFormat(const char* f) { copyString(format, f, MAX_FORMAT); }
const char* FileFormat::getFormat() const { return format; }


ConversionSettings::ConversionSettings() {
    inputFormat[0] = '\0';
    outputFormat[0] = '\0';
    quality = 0;
}

ConversionSettings::ConversionSettings(const char* inF, const char* outF, int q) {
    setInputFormat(inF);
    setOutputFormat(outF);
    setQuality(q);
}

ConversionSettings::ConversionSettings(const ConversionSettings& cs) {
    copyString(inputFormat, cs.inputFormat, MAX_FORMAT);
    copyString(outputFormat, cs.outputFormat, MAX_FORMAT);
    quality = cs.quality;
}

ConversionSettings::~ConversionSettings() {}

void ConversionSettings::setInputFormat(const char* f) { copyString(inputFormat, f, MAX_FORMAT); }
void ConversionSettings::setOutputFormat(const char* f) { copyString(outputFormat, f, MAX_FORMAT); }
void ConversionSettings::setQuality(int q) { quality = q; }

const char* ConversionSettings::getInputFormat() const { return inputFormat; }
const char* ConversionSettings::getOutputFormat() const { return outputFormat; }
int ConversionSettings::getQuality() const { return quality; }


Converter::Converter() { name[0] = '\0'; }

Converter::Converter(const char* n, const char* inF, const char* outF) {
    setName(n);
    setInputFormat(inF);
    setOutputFormat(outF);
}

Converter::Converter(const Converter& c) {
    copyString(name, c.name, MAX_NAME);
    inputFormat = c.inputFormat;
    outputFormat = c.outputFormat;
}

Converter::~Converter() {}

void Converter::setName(const char* n) { copyString(name, n, MAX_NAME); }
void Converter::setInputFormat(const char* f) { inputFormat.setFormat(f); }
void Converter::setOutputFormat(const char* f) { outputFormat.setFormat(f); }

const char* Converter::getName() const { return name; }
const char* Converter::getInputFormat() const { return inputFormat.getFormat(); }
const char* Converter::getOutputFormat() const { return outputFormat.getFormat(); }


ConversionResult::ConversionResult() {
    userName[0] = '\0';
    format[0] = '\0';
    success = 0;
}

ConversionResult::ConversionResult(const char* user, const char* fmt, int ok) {
    copyString(userName, user, MAX_NAME);
    copyString(format, fmt, MAX_FORMAT);
    success = ok;
}

ConversionResult::ConversionResult(const ConversionResult& r) {
    copyString(userName, r.userName, MAX_NAME);
    copyString(format, r.format, MAX_FORMAT);
    success = r.success;
}

ConversionResult::~ConversionResult() {}

const char* ConversionResult::getUserName() const { return userName; }
const char* ConversionResult::getFormat() const { return format; }
int ConversionResult::isSuccess() const { return success; }


int inputInt(const char* msg) {
    int v;
    while (true) {
        cout << msg;

        if (cin >> v) {
            if (cin.peek() != '\n' && cin.peek() != ' ' && !cin.eof()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Ошибка! Введите целое число!\n";
                continue;
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        else {
            cout << "Ошибка! Введите целое число!\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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


void addConverter() {
    if (convertersCount >= convertersMax) {
        cout << "Нет места для новых конверторов.\n";
        return;
    }

    char name[MAX_NAME];
    char inF[MAX_FORMAT];
    char outF[MAX_FORMAT];

    inputString(name, MAX_NAME, "Название конвертора: ");
    inputString(inF, MAX_FORMAT, "Входной формат: ");
    inputString(outF, MAX_FORMAT, "Выходной формат: ");

    converters[convertersCount] = SmartPointer<Converter>(new Converter(name, inF, outF));
    convertersCount++;

    cout << "Конвертор добавлен.\n";
}


void performConversion() {
    if (convertersCount == 0) {
        cout << "Нет конверторов.\n";
        return;
    }

    cout << "Список конверторов:\n";
    for (int i = 0; i < convertersCount; i++) {
        cout << i << ": " << converters[i]->getName()
            << " (" << converters[i]->getInputFormat()
            << " -> " << converters[i]->getOutputFormat() << ")\n";
    }

    int idx = inputInt("Выберите номер: ");
    if (idx < 0 || idx >= convertersCount) {
        cout << "Неверный номер.\n";
        return;
    }

    char userName[MAX_NAME];
    inputString(userName, MAX_NAME, "Имя пользователя: ");

    int quality = inputInt("Качество (1..100): ");

    ConversionSettings newSettings(converters[idx]->getInputFormat(),
        converters[idx]->getOutputFormat(), quality);

    Transaction<ConversionSettings> tr;

    tr.beginTransaction(newSettings);

    bool valid = (quality >= 1 && quality <= 100);

    if (!valid) {
        tr.rollback();
        logs[logsCount++] = ConversionResult(userName, converters[idx]->getOutputFormat(), 0);
        cout << "Ошибка: некорректные параметры.\n";
    }
    else {
        tr.commit();
        logs[logsCount++] = ConversionResult(userName, converters[idx]->getOutputFormat(), 1);
        cout << "Конвертация выполнена.\n";
    }
}


void showLogsForUserAndFormat() {
    if (logsCount == 0) {
        cout << "Нет записей.\n";
        return;
    }

    char userName[MAX_NAME];
    char fmt[MAX_FORMAT];

    inputString(userName, MAX_NAME, "Имя пользователя: ");
    inputString(fmt, MAX_FORMAT, "Формат: ");

    bool found = false;

    for (int i = 0; i < logsCount; i++) {
        if (equalString(logs[i].getUserName(), userName) &&
            equalString(logs[i].getFormat(), fmt)) {

            found = true;
            cout << "- " << (logs[i].isSuccess() ? "Успех" : "Ошибка") << endl;
        }
    }

    if (!found) cout << "Нет записей.\n";
}


void printMenu() {
    cout << "\n======= МЕНЮ =======\n";
    cout << "1 - Добавить конвертор\n";
    cout << "2 - Выполнить конвертацию (с транзакцией)\n";
    cout << "3 - Показать логи\n";
    cout << "0 - Выход\n";
    cout << "====================\n";
}
