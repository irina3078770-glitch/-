#include<iostream>
#include<windows.h>
#include "converter.h"

using namespace std;

int main() {
   
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "rus");

    convertersMax = 20;
    converters = new SmartPointer<Converter>[convertersMax];
    convertersCount = 0;

    logsMax = 100;
    logs = new ConversionResult[logsMax];
    logsCount = 0;


    while (true) {
        printMenu();
        int cmd = inputInt("Ваш выбор: ");

        switch (cmd) {

        case 1:
            addConverter();
            break;

        case 2:
            performConversion();
            break;

        case 3:
            showLogsForUserAndFormat();
            break;

        case 0: {
            cout << "До свидания.\n";
            delete[] converters;
            delete[] logs;
            return 0;
        }

        default:
            cout << "Нет такого пункта меню.\n";
            break;
        }
    }
    return 0;
}

