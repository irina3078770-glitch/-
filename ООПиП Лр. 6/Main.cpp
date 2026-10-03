/*Построить иерархию классов согласно схеме наследования,
приведенной на рисунке ниже по предметной области «HR-менеджмент».
Каждый класс должен содержать необходимые конструкторы и методы
работы с полями классов. Функция main() должна иллюстрировать работу с
массивами объектов всех созданных классов. При необходимости атрибуты
доступа при наследовании можно изменять. При необходимости
самостоятельно добавить классы для реализации множественного
наследования.
*/

#include <iostream>
#include <fstream>
#include <limits>
#include <cctype> //для классификации и преобразования отдельных типов
#include "hr.h"

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

            // Разрешаем буквы (латиница/кириллица) и пробелы
            if (c < 128 && !isalpha(c) && c != ' ') {
                ok = false;
                break;
            }
        }

        if (ok) break;

        cout << "Ошибка! Допускаются только буквы и пробелы.\n";
    }
}

Employee** a = nullptr;
int countEmp = 0;
int capEmp = 0;

void ensureCapacity() {
    if (countEmp < capEmp) return;

    int newCap = (capEmp == 0 ? 2 : capEmp * 2);
    Employee** newA = new Employee * [newCap];

    for (int i = 0; i < countEmp; i++) {
        newA[i] = a[i];
    }
    delete[] a;
    a = newA;
    capEmp = newCap;
}

int main() {
    setlocale(0, "rus");

    int choice;

    do {
        cout << "\n========== МЕНЮ ==========\n";
        cout << "1 - Добавить консультанта\n";
        cout << "2 - Добавить менеджера\n";
        cout << "3 - Добавить консультанта-менеджера\n";
        cout << "4 - Добавить постоянного менеджера\n";
        cout << "5 - Добавить директора\n";
        cout << "6 - Показать всех сотрудников\n";
        cout << "7 - Сохранить в файл\n";
        cout << "0 - Выход\n";
        cout << "===========================\n";

        choice = inputInt("Ваш выбор: ");

        switch (choice) {

        case 1: {
            ensureCapacity();

            char name[50], project[50];
            inputString(name, 50, "ФИО: ");
            int age = inputInt("Возраст: ");
            double salary = inputDouble("Зарплата: ");
            int days = inputInt("Срок контракта (дней): ");
            inputString(project, 50, "Проект: ");

            a[countEmp++] = new Consultant(name, age, salary, days, project);
            break;
        }

        case 2: {
            ensureCapacity();

            char name[50];
            inputString(name, 50, "ФИО: ");
            int age = inputInt("Возраст: ");
            double salary = inputDouble("Зарплата: ");
            int team = inputInt("Размер команды: ");

            a[countEmp++] = new Manager(name, age, salary, team);
            break;
        }

        case 3: {
            ensureCapacity();

            char name[50], project[50];
            inputString(name, 50, "ФИО: ");
            int age = inputInt("Возраст: ");
            double salary = inputDouble("Зарплата: ");
            int days = inputInt("Срок контракта (дней): ");
            inputString(project, 50, "Проект: ");
            int team = inputInt("Размер команды: ");

            a[countEmp++] = new ConsultantManager(name, age, salary, days, project, team);
            break;
        }

        case 4: {
            ensureCapacity();

            char name[50];
            inputString(name, 50, "ФИО: ");
            int age = inputInt("Возраст: ");
            double salary = inputDouble("Зарплата: ");
            int exp = inputInt("Стаж (лет): ");
            int team = inputInt("Размер команды: ");

            a[countEmp++] = new PermanentManager(name, age, salary, exp, team);
            break;
        }

        case 5: {
            ensureCapacity();

            char name[50];
            inputString(name, 50, "ФИО: ");
            int age = inputInt("Возраст: ");
            double salary = inputDouble("Зарплата: ");
            int team = inputInt("Размер команды: ");
            int lvl = inputInt("Уровень директора: ");

            a[countEmp++] = new Director(name, age, salary, team, lvl);
            break;
        }

        case 6: {
            if (countEmp == 0) {
                cout << "Сотрудников пока нет.\n";
                break;
            }
            cout << "\n------ СПИСОК СОТРУДНИКОВ -----\n";
            for (int i = 0; i < countEmp; i++) {
                cout << i + 1 << ") ";
                a[i]->print();
                cout << endl;
            }
            break;
        }

        case 7: {
            ofstream out("employees.txt");
            if (!out) {
                cout << "Ошибка открытия файла!\n";
                break;
            }

            for (int i = 0; i < countEmp; i++) {
                a[i]->save(out);
                out << endl;
            }

            out.close();
            cout << "Данные сохранены в файл\n";
            break;
        }

        case 0:
            cout << "До свидания!\n";
            break;

        default:
            cout << "Нет такого пункта.\n";
        }

    } while (choice != 0);

    for (int i = 0; i < countEmp; i++) {
        delete a[i];
    }
    delete[] a;

    return 0;
}
