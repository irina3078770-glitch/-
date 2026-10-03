/*
Разработать набор классов (минимум 5) по теме «Конвертор
файлов». Корректно реализовать связи между классами. Использовать
smart-указатели для создания программы учета конверторов файлов.
Реализовать механизм транзакций, который позволит откатывать изменения,
если данные о выбранном конверторе файлов введены неверно (например,
формат или качество итогового файла имеют некорректное значение). В
разработанном наборе классов должен быть хотя бы один шаблонный класс.
Все классы должны иметь методы получения и установки значений полей.
Программа должна обеспечивать вывод информации обо всех выполненных
успешно и неуспешно конвертациях для отдельного пользователя и формата
файлов. Использовать конструктор с параметрами, конструктор без
параметров, конструктор копирования, деструктор.
*/
#pragma once
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

const int MAX_NAME = 50;
const int MAX_FORMAT = 10;






//функции работы со строками
void copyString(char* dest, const char* src, int maxLen);
bool equalString(const char* a, const char* b);


class User {
private:
    char name[MAX_NAME];

public:
    User();
    User(const char* n);
    User(const User& u);
    ~User();

    void setName(const char* n);
    const char* getName() const;
};

class FileFormat {
private:
    char format[MAX_FORMAT];

public:
    FileFormat();
    FileFormat(const char* f);
    FileFormat(const FileFormat& ff);
    ~FileFormat();

    void setFormat(const char* f);
    const char* getFormat() const;
};


//настройки конвертации 
class ConversionSettings {
private:
    char inputFormat[MAX_FORMAT];
    char outputFormat[MAX_FORMAT];
    int quality;

public:
    ConversionSettings();
    ConversionSettings(const char* inF, const char* outF, int q);
    ConversionSettings(const ConversionSettings& cs);
    ~ConversionSettings();

    void setInputFormat(const char* f);
    void setOutputFormat(const char* f);
    void setQuality(int q);

    const char* getInputFormat() const;
    const char* getOutputFormat() const;
    int getQuality() const;
};

class Converter {
private:
    char name[MAX_NAME];
    FileFormat inputFormat;
    FileFormat outputFormat;

public:
    Converter();
    Converter(const char* n, const char* inF, const char* outF);
    Converter(const Converter& c);
    ~Converter();

    void setName(const char* n);
    void setInputFormat(const char* f);
    void setOutputFormat(const char* f);

    const char* getName() const;
    const char* getInputFormat() const;
    const char* getOutputFormat() const;
};

//запись в журнале
class ConversionResult {
private:
    char userName[MAX_NAME];
    char format[MAX_FORMAT];
    int success;

public:
    ConversionResult();
    ConversionResult(const char* user, const char* fmt, int ok);
    ConversionResult(const ConversionResult& r);
    ~ConversionResult();

    const char* getUserName() const;
    const char* getFormat() const;
    int isSuccess() const;
};



template <class T>
class Status {
public:
    T* ptr;
    int counter;

    Status(T* p = NULL) {
        ptr = p;
        counter = (p ? 1 : 0);
    }
};

//умный указатель
template <class T>
class SmartPointer {
private:
    Status<T>* smartPtr;

public:
    SmartPointer(T* ptr = NULL) {
        if (!ptr) smartPtr = NULL;
        else smartPtr = new Status<T>(ptr);
    }

    SmartPointer(const SmartPointer& obj) {
        smartPtr = obj.smartPtr;
        if (smartPtr) smartPtr->counter++;
    }

    ~SmartPointer() {
        if (smartPtr) {
            smartPtr->counter--;
            if (smartPtr->counter == 0) {
                delete smartPtr->ptr; 
                delete smartPtr; 
            }
        }
    }

    SmartPointer& operator=(const SmartPointer& obj) {
        if (this != &obj) {
            if (smartPtr) {
                smartPtr->counter--;
                if (smartPtr->counter == 0) {
                    delete smartPtr->ptr;
                    delete smartPtr;
                }
            }
            smartPtr = obj.smartPtr;
            if (smartPtr) smartPtr->counter++;
        }
        return *this;
    }

    T* operator->() const {
        return smartPtr ? smartPtr->ptr : NULL;
    }
};

//механизм транзакций
template <class T>
class Transaction {
private:
    T* currentState;
    T* prevState;

public:
    Transaction() {
        prevState = NULL;
        currentState = new T;
    }

    ~Transaction() {
        delete currentState;
        delete prevState;
    }

    int beginTransaction(const T& newState) {
        delete prevState;
        prevState = currentState;
        currentState = new T(*prevState);
        *currentState = newState;
        return 1;
    }

    void commit() {
        delete prevState;
        prevState = NULL;
    }

    void rollback() {
        if (prevState) {
            delete currentState;
            currentState = prevState;
            prevState = NULL;
        }
    }

    T* operator->() {
        return currentState;
    }
};

// Глобальные динамические массивы
extern SmartPointer<Converter>* converters;
extern int convertersCount;
extern int convertersMax;

extern ConversionResult* logs;
extern int logsCount;
extern int logsMax;

int inputInt(const char* msg);
void inputString(char* buffer, int maxLen, const char* msg);

void addConverter();
void performConversion();
void showLogsForUserAndFormat();
void printMenu();
