//Создать классы Circle, Square, Triangle, Shape, Oval, Sphere с
//необходимым набором полей и методов. Создать методы нахождения
//площади и объема фигур. Создать массив объектов базового класса и
//заполнить этот массив объектами базового и производных классов. Написать
//программу, которая создает объекты каждого из этих классов, и находит
//фигуру максимальную по площади и по объему, выводит данные о фигурах
//на экран и в файл. Классы должны содержать методы получения и изменения
//значений всех полей. Все поля классов должны быть объявлены с атрибутами
//private или protected.
#include <iostream>
#include <fstream>
#include <limits>
#include "Header 4.h"

using namespace std;

double inputDouble(const char* msg) {
    double v;
    while (true) {
        cout << msg;

        if (cin >> v) {
            // Проверка на лишние символы
            if (cin.peek() != '\n' && cin.peek() != ' ' && !cin.eof()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка! Введите число!\n";
                continue;
            }
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

double getArea(Shape* s) {
    switch (s->getType()) {
    case 1: return ((Circle*)s)->area();
    case 2: return ((Square*)s)->area();
    case 3: return ((Triangle*)s)->area();
    case 4: return ((Oval*)s)->area();
    case 5: return ((Sphere*)s)->area();
    }
    return 0;
}

double getVolume(Shape* s) {
    switch (s->getType()) {
    case 1: return ((Circle*)s)->volume();
    case 2: return ((Square*)s)->volume();
    case 3: return ((Triangle*)s)->volume();
    case 4: return ((Oval*)s)->volume();
    case 5: return ((Sphere*)s)->volume();
    }
    return 0;
}

void printShape(Shape* s, ostream& os) {
    switch (s->getType()) {
    case 1: ((Circle*)s)->print(os); break;
    case 2: ((Square*)s)->print(os); break;
    case 3: ((Triangle*)s)->print(os); break;
    case 4: ((Oval*)s)->print(os); break;
    case 5: ((Sphere*)s)->print(os); break;
    }
}

Shape** a = new Shape * [2];
int countShapes = 0;
int capacityShapes = 2;

void ensureCapacity() {
    if (countShapes == capacityShapes) {
        int newCap = (capacityShapes == 0 ? 2 : capacityShapes * 2);

        Shape** newA = new Shape * [newCap];

        for (int i = 0; i < countShapes; i++)
            newA[i] = a[i];

        delete[] a;
        a = newA;
        capacityShapes = newCap;
    }
}

int main() {
    setlocale(0, "rus");

    bool running = true;

    while (running) {

        cout << "\n============= ГЛАВНОЕ МЕНЮ =============\n";
        cout << "1 - Добавить фигуру\n";
        cout << "2 - Найти фигуру с максимальной площадью\n";
        cout << "3 - Найти фигуру с максимальным объёмом\n";
        cout << "4 - Показать все фигуры\n";
        cout << "5 - Очистить файл\n";
        cout << "6 - Выход\n";
        cout << "==========================================\n";

        int choice = inputInt("Ваш выбор: ");

        switch (choice) {

        case 1: {
            cout << "\nКакую фигуру хотите добавить?\n";
            cout << "1 - Круг\n";
            cout << "2 - Квадрат\n";
            cout << "3 - Треугольник\n";
            cout << "4 - Овал\n";
            cout << "5 - Сфера\n";
            cout << "6 - Назад\n";

            int t = inputInt("Ваш выбор: ");

            if (t == 6) {
                cout << "Возврат в главное меню...\n";
                break;
            }

            ensureCapacity();

            if (t == 1) {
                a[countShapes++] = new Circle(inputDouble("Введите радиус: "));
            }
            else if (t == 2) {
                a[countShapes++] = new Square(inputDouble("Введите сторону: "));
            }
            else if (t == 3) {
                a[countShapes++] = new Triangle(
                    inputDouble("Основание: "),
                    inputDouble("Высота: ")
                );
            }
            else if (t == 4) {
                a[countShapes++] = new Oval(
                    inputDouble("Полуось a: "),
                    inputDouble("Полуось b: ")
                );
            }
            else if (t == 5) {
                a[countShapes++] = new Sphere(inputDouble("Введите радиус: "));
            }
            else {
                cout << "Нет такой фигуры.\n";
                break;
            }

            cout << "Фигура успешно добавлена!\n";
            break;
        }
         //максимальная площадь
        case 2: {
            if (countShapes == 0) {
                cout << "Нет фигур.\n";
                break;
            }

            Shape* maxA = a[0];
            for (int i = 1; i < countShapes; i++) {
                if (getArea(a[i]) > getArea(maxA))
                    maxA = a[i];
            }
            cout << "\nФигура с максимальной площадью:\n";
            printShape(maxA, cout);
            cout << "Площадь: " << getArea(maxA) << "\n";
            break;
        }

         //максимальный объём
        case 3: {
            if (countShapes == 0) {
                cout << "Нет фигур.\n";
                break;
            }

            Shape* maxV = a[0];
            for (int i = 1; i < countShapes; i++) {
                if (getVolume(a[i]) > getVolume(maxV))
                    maxV = a[i];
            }

            cout << "\nФигура с максимальным объёмом:\n";
            printShape(maxV, cout);
            cout << "Объём: " << getVolume(maxV) << "\n";
            break;
        }

         //показать все фигуры
        case 4: {
            if (countShapes == 0) {
                cout << "Нет фигур.\n";
                break;
            }

            ofstream fout("output.txt", ios::app);

            for (int i = 0; i < countShapes; i++) {
                cout << "Фигура #" << i + 1 << ":\n";
                printShape(a[i], cout);
                cout << "Площадь: " << getArea(a[i]) << "\n";
                cout << "Объём: " << getVolume(a[i]) << "\n\n";

                fout << "Фигура #" << i + 1 << ":\n";
                printShape(a[i], fout);
                fout << "Площадь: " << getArea(a[i]) << "\n";
                fout << "Объём: " << getVolume(a[i]) << "\n\n";
            }

            fout.close();
            cout << "Данные записаны в файл\n";
            break;
        }

         //очистить файл
        case 5: {
            ofstream fout("output.txt", ios::trunc);
            fout.close();
            cout << "Файл очищен!\n";
            break;
        }

         //выход
        case 6:
            running = false;
            cout << "До свидания!\n";
            break;

        default:
            cout << "Нет такого пункта меню.\n";
        }
    }

    // Освобождение памяти
    for (int i = 0; i < countShapes; i++)
        delete a[i];

    delete[] a;

    return 0;
}

