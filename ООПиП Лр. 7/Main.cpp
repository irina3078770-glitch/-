#include<iostream>
#include<windows.h>
#include "Converter.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "rus");

    ConverterSystem sys;

    while (true) {
        cout << "\n----- МЕНЮ -----\n";
        cout << "1 - Добавить пользователя\n";
        cout << "2 - Выполнить конвертацию\n";
        cout << "3 - Показать конвертации по пользователю\n";
        cout << "4 - Показать конвертации по формату\n";
        cout << "0 - Выход\n";
        cout << "----------------\n";

        int choice = inputInt("Ваш выбор: ");

        switch (choice) {
        case 1: {
            sys.addUser();
            break;
        }
        case 2: {
            sys.doConversion();
            break;
        }
        case 3: {
            sys.showLogsByUser();
            break;
        }
        case 4: {
            sys.showLogsByFormat();
            break;
        }
        case 0: {
            cout << "До свидания\n";
            return 0;
        }
        default:
            cout << "Неверный пункт.\n";
        }
    }
}
