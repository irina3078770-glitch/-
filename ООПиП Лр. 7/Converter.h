/*Разработать набор классов (минимум 5) по теме «Конвертор
файлов». Корректно реализовать связи между классами. В разработанном
наборе классов должен быть хотя бы один шаблонный класс. Все классы
должны иметь методы получения и установки значений полей. Программа
должна обеспечивать вывод информации обо всех выполненных успешно и
неуспешно конвертациях для отдельного пользователя и формата файлов.
Использовать конструктор с параметрами, конструктор без параметров,
конструктор копирования, деструктор.
*/

#pragma once
#include <iostream>
#include <limits>
#include <cstring>

using namespace std;


int inputInt(const char* msg);
double inputDouble(const char* msg);
void inputString(char* buffer, int maxLen, const char* msg);

class User {
    int id;
    char name[64];
public:
    User();
    User(int id, const char* name);
    User(const User& other);
    ~User();

    void setId(int id);
    int getId() const;

    void setName(const char* n);
    const char* getName() const;
};


class FileFormat {
    char ext[16];
public:
    FileFormat();
    FileFormat(const char* e);
    FileFormat(const FileFormat& other);
    ~FileFormat();

    void setExt(const char* e);
    const char* getExt() const;
};


class ConversionRecord {
    int userId;
    char fromExt[16];
    char toExt[16];
    bool success;
public:
    ConversionRecord();
    ConversionRecord(int userId, const char* fromE, const char* toE, bool success);
    ConversionRecord(const ConversionRecord& other);
    ~ConversionRecord();

    void setUserId(int id);
    int getUserId() const;

    void setFromExt(const char* e);
    const char* getFromExt() const;

    void setToExt(const char* e);
    const char* getToExt() const;

    void setSuccess(bool s);
    bool isSuccess() const;
};

//Шаблонный класс Converter<T>
template <class T>
class Converter {
public:
    Converter() {}
    Converter(const Converter<T>&) {}
    ~Converter() {}

    bool convert(const T& in, T& out) {
        out = in; // имитация конвертации
        return true;
    }
};


//Основная система 
class ConverterSystem {
    static const int MAX_USERS = 20;
    static const int MAX_RECORDS = 200;

    User users[MAX_USERS];
    int userCount;

    ConversionRecord records[MAX_RECORDS];
    int recordCount;

public:
    ConverterSystem();
    ConverterSystem(const ConverterSystem& other);
    ~ConverterSystem();

    void addUser();
    User* findUserById(int id);

    void doConversion();
    void showLogsByUser();
    void showLogsByFormat();
};