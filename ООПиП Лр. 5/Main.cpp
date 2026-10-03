/*Создать классы «Учащийся колледжа», «Школьник», «Студент» с
необходимым набором полей и методов. Все классы должны содержать
методы получения и изменения всех полей. Программа должна выдавать
сведения об учащихся, имеющих количество пропусков больше указанного
пользователем. Использовать конструктор с параметрами, конструктор без
параметров, конструктор копирования. В класс добавить необходимый набор
полей и методов (минимум два поля и два метода) на свое усмотрение.
Предусмотреть метод для записи полученных данных в файл.*/
#include<iostream>
#include<fstream>
#include"Person.h"

using namespace std;

void ensureCapacity(Person**& a, int& count, int& capacity) {
    if (count < capacity && a != nullptr)
        return;

    int newCap = (capacity == 0) ? 2 : capacity * 2;
    if (newCap <= count) newCap = count + 1;

    Person** newA = new Person * [newCap];

    for (int i = 0; i < newCap; i++) {
        newA[i] = nullptr;
    }

    for (int i = 0; i < count; i++) {
        if (a != nullptr) { 
            newA[i] = a[i];
        }
    }

    delete[] a;
    a = newA;
    capacity = newCap;
}

int main() {
	setlocale(0, "rus");
    Person** a = nullptr;
    int count = 0;
    int capacity = 0;

    int choice;
    do {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1 - Добавить школьника\n";
        cout << "2 - Добавить учащегося колледжа\n";
        cout << "3 - Добавить студента\n";
        cout << "4 - Показать всех\n";
        cout << "5 - Показать с пропусками больше n\n";
        cout << "6 - Записать в файл\n";
        cout << "0 - Выход\n ";
        cout << "Ваш выбор: \n";
        choice = inputInt("");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice < 0 || choice>6) {
            cout << "Ошибка! Нет такого пункта меню\n";
        }

        switch (choice) {
        case 1: {
            ensureCapacity(a, count, capacity);

            char fio[50];

            inputFio(fio, 50, "ФИО: ");
            int age = inputInt("Возраст: ");
            int abs = inputInt("Пропуски: ");
            int grade = inputInt("Класс: ");
            int schoolNumber = inputInt("Номер школы: "); 
            a[count] = new Schoolboy(fio, age, abs, grade, schoolNumber);
            count++;
            break;
        }
        case 2: {
            ensureCapacity(a, count, capacity);
            char fio[50], spec[50];

            inputFio(fio, 50, "ФИО: ");
            inputFio(spec, 50, "Специальность: ");

            int age = inputInt("Возраст: ");
            int abs = inputInt("Пропуски: ");
            int course = inputInt("Курс: ");

            a[count] = new CollegeStudent(fio, age, abs, spec, course);
            count++;
            break;
        }
        case 3: {
            ensureCapacity(a, count, capacity);

            char fio[50], faculty[50];

            inputFio(fio, 50, "ФИО: ");
            inputFio(faculty, 50, "Факультет: ");

            int age = inputInt("Возраст: ");
            int abs = inputInt("Пропуски: ");
            int year = inputInt("Курс: ");

            a[count] = new UniversityStudent(fio, age, abs, faculty, year);
            count++;
            break;
        }
        case 4: {
            if (count == 0) {
                cout << "Список пуст.\n";
                break;
            }

            cout << "\n===== СПИСОК УЧАЩИХСЯ =====\n";
            for (int i = 0; i < count; i++) {
                a[i]->print();
            }
            break;
        }
        case 5: {
            int n = inputInt("Введите n: ");
            bool found = false;
            cout << "\n===== Учащиеся с пропусками > " << n << " =====\n";
            for (int i = 0; i < count; i++) {
                if (a[i]->manyAbsences(n)) {
                    a[i]->print();
                    found = true;
                }
            }
            if (!found) {
                cout << "Учащихся с количеством пропусков больше " << n << " не обнаружено.\n";
            }
            break;
        }
        case 6: {
            ofstream out("students.txt");

            if (!out) {
                cout << "Ошибка открытия файла!\n";
                break;
            }

            for (int i = 0; i < count; i++) {
                a[i]->saveToFile(out);
            }

            out.close();
            cout << "Файл успешно сохранён.\n";
            break;
        }
        case 0: {
            cout << "До свидания\n";
            break;
        }
        default: {
            cout << "Ошибка! Нет такого пункта меню.\n";
            break;
        }
        }
     
    }while (choice != 0);
    for (int i = 0; i < count; i++) {
        delete a[i];
    }
    delete[] a;

    return 0;
} 

