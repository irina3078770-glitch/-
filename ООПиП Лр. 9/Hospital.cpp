#include"Hospital.h"

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
        cout << "Ошибка! Введите целое число!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        cout << "Ошибка! Введите число!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        for (int i = 0; buffer[i]; i++) {
            unsigned char c = buffer[i];
            if (c < 128 && !isalpha(c) && c != ' ')
                ok = false;
        }
        if (ok) break;
        cout << "Ошибка! Допускаются только буквы и пробелы.\n";
    }
}

StaffException::StaffException(const char* m) : msg(m) {}
const char* StaffException::what() const { return msg; }


Staff::Staff() {
    cout << "Конструктор Staff\n";
    name[0] = '\0';
    age = 0;
}
Staff::~Staff() {
    cout << "Деструктор Staff: " << name << "\n";
}

void Staff::input() {
    inputString(name, 50, "Введите имя сотрудника: ");
    age = inputInt("Введите возраст: ");
    if (age <= 0) throw StaffException("Возраст должен быть положительным");
}
void Staff::print() const {
    cout << "Сотрудник: " << name << ", возраст: " << age << "\n";
}


Doctor::Doctor() : Staff() {
    cout << "Конструктор Doctor\n";
}

Doctor::~Doctor() {
    cout << "Деструктор Doctor: " << name << "\n";
}
void Doctor::input() {
    Staff::input();
    exp = inputInt("Введите стаж врача: ");
    if (exp < 0)
        throw "Стаж врача не может быть отрицательным";
}
void Doctor::print() const {
    cout << "Врач: " << name << ", стаж: " << exp << "\n";
}


Nurse::Nurse() : Staff() {
    cout << "Конструктор Nurse\n";
}
Nurse::~Nurse() {
    cout << "Деструктор Nurse: " << name << "\n";
}
void Nurse::input() {
    Staff::input();
    shift = inputInt("Введите смену (1-3): ");
    if (shift < 1 || shift > 3) throw 1;
}
void Nurse::print() const {
    cout << "Медсестра: " << name << ", смена: " << shift << "\n";
}


Technician::Technician() : Staff() {
    cout << "Конструктор Technician\n";
}
Technician::~Technician() {
    cout << "Деструктор Technician: " << name << "\n";
}
void Technician::input() {
    Staff::input();
    salary = inputDouble("Введите зарплату: ");
    if (salary < 0) throw 3.14;
}
void Technician::print() const {
    cout << "Техник: " << name << ", зарплата: " << salary << "\n";
}


Ward::Ward() {
    cout << "Конструктор Ward\n";
    number = 0;
    beds = 0;
}
Ward::~Ward() {
    cout << "Деструктор Ward\n";
}
void Ward::input() {
    number = inputInt("Введите номер палаты: ");
    beds = inputInt("Введите количество кроватей: ");
    if (beds <= 0) throw StaffException("Количество кроватей должно быть > 0");
}
void Ward::print() const {
    cout << "Палата №" << number << ", коек: " << beds << "\n";
}


Department::Department() {
    cout << "Конструктор Department\n";
    name[0] = '\0';
    count = 0;
    for (int i = 0; i < 10; i++) staff[i] = 0;
}
Department::~Department() {
    cout << "Деструктор Department: " << name << "\n";
}
void Department::input() {
    inputString(name, 50, "Введите название отделения: ");
    ward.input();
}
void Department::add(Staff* s) {
    if (count >= 10) throw "Нет мест для персонала";
    staff[count++] = s;
}
void Department::print() const {
    cout << "Отделение: " << name << "\n";
    ward.print();
    cout << "Персонал:\n";
    for (int i = 0; i < count; i++) {
        staff[i]->print();
    }
}


Hospital::Hospital() {
    cout << "Конструктор Hospital\n";
    name[0] = '\0';
    total = 0;
    for (int i = 0; i < 20; i++) all[i] = 0;
}
Hospital::~Hospital() {
    cout << "Деструктор Hospital: " << name << "\n";
    for (int i = 0; i < total; i++) delete all[i];
}
void Hospital::input() {
    inputString(name, 50, "Введите название учреждения: ");
    dept.input();
}

void Hospital::addDoctor() {
    Doctor* d = new Doctor;
    try {
        d->input();
        all[total++] = d;
        dept.add(d);
    }
    catch (...) {
        delete d;
        throw;
    }
}

void Hospital::addNurse() {
    Nurse* n = new Nurse;
    try {
        n->input();
        all[total++] = n;
        dept.add(n);
    }
    catch (...) {
        delete n;
        throw;
    }
}
void Hospital::addTech() {
    Technician* t = new Technician;
    try {
        t->input();
        all[total++] = t;
        dept.add(t);
    }
    catch (...) {
        delete t;
        throw;
    }
}
void Hospital::print() const {
    cout << "\n=== Медицинское учреждение: " << name << " ===\n";
    dept.print();
}


void myTerminate() {
    cout << "\nФункция myTerminate() вызвана terminate().\n";
    exit(-1);
}