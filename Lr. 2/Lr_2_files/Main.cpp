#include <iostream>
#include <Windows.h>
#include "Shop.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    OrderManager manager;
    int choice;

    do {
        cout << "-------МЕНЮ-------\n";
        cout << "1 - Посмотреть заказ\n";
        cout << "2 - Добавить материал\n";
        cout << "3 - Редактировать\n";
        cout << "4 - Удалить\n";
        cout << "5 - Поиск\n";
        cout<<"0 - Выход\n";
        choice = inputInt("Ваш выбор: ");

        switch (choice) {
        case 1: manager.displayAll(); break;
        case 2: manager.addRecord(); break;
        case 3: manager.editRecord(inputInt("Номер записи: ")); break;
        case 4: manager.deleteRecord(inputInt("Номер записи: ")); break;
        case 5: {
            char q[50];
            inputString(q, 50, "Название: ");
            manager.searchByName(q);
            break;
        }
        case 0: cout << "До свидания!\n"; break;

        default: cout << "Ошибка! Нет такого пункта меню.\n"; break;
        }
    } while (choice != 0);

    return 0;
}