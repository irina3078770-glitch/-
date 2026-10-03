/*Создать классы «Учащийся колледжа», «Школьник», «Студент» с
необходимым набором полей и методов. Все классы должны содержать
методы получения и изменения всех полей. Программа должна выдавать
сведения об учащихся, имеющих количество пропусков больше указанного
пользователем. Использовать конструктор с параметрами, конструктор без
параметров, конструктор копирования. В класс добавить необходимый набор
полей и методов (минимум два поля и два метода) на свое усмотрение.
Предусмотреть метод для записи полученных данных в файл.*/

#include<iostream>
#include"Person.h"

using namespace std;

Person::Person() {
	fio[0] = '\0';
	age = 0;
	absences = 0;
}

Person::Person(const char* f, int a, int b) {
    strncpy_s(fio, f, 49);
	fio[49] = '\0';
	age = a;
	absences = b;
}

Person::Person(const Person& other) {
    strncpy_s(fio, other.fio, 49);
	fio[49] = '\0';
	age = other.age;
	absences = other.absences;
}

const char* Person::getFio() const { 
	return fio; 
}
int Person::getAge() const { 
	return age;
}
int Person::getAbsences() const { 
	return absences; 
}

void Person::setFio(const char* f) { 
    strncpy_s(fio, f, 49);
	fio[49] = '\0'; 
}
void Person::setAge(int a) { 
	age = a; 
}
void Person::setAbsences(int a) { 
	absences = a; 
}

/* Метод 2 — проверка количества пропусков */
bool Person::manyAbsences(int limit) const {
	return absences > limit;
}

Schoolboy::Schoolboy() : Person() {
	grade = 0;
	school = 0;
}

Schoolboy::Schoolboy(const char* f, int a, int b, int g, int n) : Person(f, a, b) {
	grade = g;
	school=n;
	
}

Schoolboy::Schoolboy(const Schoolboy& s) : Person(s) {
	grade = s.grade;
    school = s.school;
}

const char* Schoolboy::getStatus() const {
	return "Школьник";
}
void Schoolboy::print() const {
	cout << "Школьник: " << fio << endl;
	cout << "возраст: " << age << endl;
	cout << "пропуски: " << absences << endl;
	cout << "класс: " << grade << endl;
	cout << "школа: " << school << endl;
}

void Schoolboy::saveToFile(ofstream& out) const {
	out << "Школьник;" << fio << ";" << age << ";" << absences
		<< ";" << grade << ";" << school << "\n";
}


CollegeStudent::CollegeStudent() : Person() {
	specialty[0] = '\0';
	course = 0;
}
CollegeStudent::CollegeStudent(const char* f, int a, int ab, const char* sp, int c)
	: Person(f, a, ab) {
    strncpy_s(specialty, sp, 49);
	specialty[49] = '\0';
	course = c;
}

CollegeStudent::CollegeStudent(const CollegeStudent& s) : Person(s) {
    strncpy_s(specialty, s.specialty, 49);
	specialty[49] = '\0';
	course = s.course;
}

const char* CollegeStudent::getStatus() const {
	return "Учащийся колледжа";
}

void CollegeStudent::print() const {
	cout << "Учащийся колледжа: " << fio << endl;
	cout << "возраст: " << age << endl;
	cout << "пропуски: " << absences << endl;
	cout << "специальность: " << specialty << endl;
	cout << "курс: " << course << endl;
}

void CollegeStudent::saveToFile(ofstream& out) const {
	out << "Колледж;" << fio << ";" << age << ";" << absences
		<< ";" << specialty << ";" << course << "\n";
}

UniversityStudent::UniversityStudent() : Person() {
    faculty[0] = '\0';
    year = 0;
}

UniversityStudent::UniversityStudent(const char* f, int a, int b, const char* fac, int y) : Person(f, a, b) {
    strncpy_s(faculty, fac, 49);
    faculty[49] = '\0';
    year = y;
}

UniversityStudent::UniversityStudent(const UniversityStudent& s) : Person(s) {
    strncpy_s(faculty, s.faculty, 49);
    faculty[49] = '\0';
    year = s.year;
}

const char* UniversityStudent::getStatus() const {
    return "Студент";
}

void UniversityStudent::print() const {
    cout << "Студент: " << fio << endl;
    cout << "возраст: " << age << endl;
    cout << "пропуски: " << absences << endl;
    cout << "факультет: " << faculty << endl;
    cout << "курс: " << year << endl;
}

void UniversityStudent::saveToFile(ofstream& out) const {
    out << "Студент;" << fio << ";" << age << ";" << absences
        << ";" << faculty << ";" << year << "\n";
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

void inputFio(char* buffer, int maxLen, const char* msg) {
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

            // Проверка: разрешаем буквы (включая кириллицу) и пробелы
            // Если c < 128, используем isalpha. Если > 128, считаем, что это кириллица (упрощенно)
            if (!isalpha(c) && c != ' ' && c < 128) {
                ok = false;
                break;
            }
        }

        if (ok) break; 

        cout << "Ошибка! Допускаются только буквы и пробелы.\n";
    }
}