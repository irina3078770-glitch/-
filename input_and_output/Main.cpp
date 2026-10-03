#include "Gym.h"

// Меню программы
void menu() {
    cout << endl << "----- МЕНЮ -----"<<endl;
    cout << "1 - Просмотреть все тренажёры"<<endl;
    cout << "2 - Добавить тренажёр" << endl;
    cout << "3 - Удалить тренажёр" << endl;
    cout << "4 - Редактировать тренажёр" << endl;
    cout << "5 - Сортировать по ID" << endl;
    cout << "6 - Поиск по названию" << endl;
    cout << "7 - Сохранить данные в файл" << endl;
    cout << "8 - Посмотреть файл " << endl;
    cout << "0 - Выход" << endl;
}

// Добавление тренажёра
void addMenu(Gym& gym) {
    cout << "\nДобавление тренажёра" << endl;

    int id = gym.generateId();
    string name = inputString("Введите название: ");

    string manName = inputString("Введите производителя: ");
    string manCountry = inputString("Введите страну производителя: ");
    Manufacturer m(manName, manCountry);

    cout << "Выберите тип тренажёра:" << endl;
    cout << "1 — Беговая дорожка" << endl;
    cout << "2 — Велотренажёр" << endl;

    int type = inputInt("Ваш выбор: ");

    if (type == 1) {
        int speed = inputInt("Максимальная скорость: ");
        int incline = inputInt("Максимальный угол наклона: ");
        gym.addEquipment(new Treadmill(id, name, m, speed, incline));
        cout << "Тренажёр добавлен." << endl;
    }
    else if (type == 2) {
        int load = inputInt("Максимальная нагрузка: ");
        int prog = inputInt("Количество программ: ");
        gym.addEquipment(new Bike(id, name, m, load, prog));
        cout << "Тренажёр добавлен." << endl;
    }
    else {
        cout << "Ошибка: неизвестный тип."<<endl;
    }
}

// Главная функция
int main() {
    setlocale(0, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Address addr("Гомель", "Советская", 10);
    Gym gym("Тренажерный зал \"Энергия\"", addr);

    Manufacturer m1("TechGym", "Германия");
    Manufacturer m2("PowerFit", "Польша");

    gym.addEquipment(new Treadmill(1, "Дорожка X100", m1, 20, 15));
    gym.addEquipment(new Bike(2, "ВелоPro 3000", m2, 120, 12));

    string filename = "gym.txt";

    while (true) {
        menu();
        int choice = inputInt("Выберите пункт меню: ");

        switch (choice) {
        case 1:
            gym.viewAll();
            break;

        case 2:
            addMenu(gym);
            break;

        case 3: {
            int id = inputInt("Введите ID для удаления: ");
            gym.deleteEquipment(id);
            break;
        }

        case 4: {
            int id = inputInt("Введите ID для редактирования: ");
            gym.editEquipment(id);
            break;
        }

        case 5:
            gym.sortById();
            break;

        case 6: {
            string part = inputString("Введите название: ");
            gym.searchByName(part);
            break;
        }

        case 7:
            gym.saveToFile(filename);
            break;

        case 8:
            gym.loadDemo(filename);
            gym.updateLastId();
            break;

        case 0:
            cout << "Выход из программы.\n";
            return 0;

        default:
            cout << "Ошибка: такого пункта нет.\n";
        }
    }

    return 0;
}
