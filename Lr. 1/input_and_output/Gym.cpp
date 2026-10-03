#include"Gym.h"

Address::Address() : city(""), street(""), building(0) {}

Address::Address(const string& c, const string& s, int b) : city(c), street(s), building(b) {}

string Address::getCity() const { return city; }
string Address::getStreet() const { return street; }
int Address::getBuilding() const { return building; }


Manufacturer::Manufacturer() : name(""), country("") {}

Manufacturer::Manufacturer(const string& n, const string& c) : name(n), country(c) {}

string Manufacturer::getName() const { return name; }
string Manufacturer::getCountry() const { return country; }


Equipment::Equipment() : id(0), name(""), manufacturer() {}

Equipment::Equipment(int id, const string& n, const Manufacturer& m) : id(id), name(n), manufacturer(m) {}

int Equipment::getId() const { return id; }
string Equipment::getName() const { return name; }
Manufacturer Equipment::getManufacturer() const { return manufacturer; }

void Equipment::setName(const string& n) { name = n; }


Treadmill::Treadmill() : Equipment(), maxSpeed(0), maxIncline(0) {}

Treadmill::Treadmill(int id, const string& n, const Manufacturer& m, int speed, int incline)
    : Equipment(id, n, m), maxSpeed(speed), maxIncline(incline) {
}

int Treadmill::getMaxSpeed() const { return maxSpeed; }
int Treadmill::getMaxIncline() const { return maxIncline; }

string Treadmill::getType() const { return "Беговая дорожка"; }


Bike::Bike() : Equipment(), maxLoad(0), programs(0) {}

Bike::Bike(int id, const string& n, const Manufacturer& m, int load, int prog)
    : Equipment(id, n, m), maxLoad(load), programs(prog) {
}

int Bike::getMaxLoad() const { return maxLoad; }
int Bike::getPrograms() const { return programs; }

string Bike::getType() const { return "Велотренажёр"; }


Gym::Gym(const string& name, const Address& addr) : gymName(name), address(addr), size(0), capacity(5) {
    a = new Equipment * [capacity];
}

Gym::~Gym() {
    for (int i = 0; i < size; i++) {
        delete a[i];
    }
    delete[] a;
}

// Увеличение массива
void Gym::resize() {
    capacity *= 2;
    Equipment** newArr = new Equipment * [capacity];

    for (int i = 0; i < size; i++) {
        newArr[i] = a[i];
    }

    delete[] a;
    a = newArr;
}

// Добавление тренажёра
void Gym::addEquipment(Equipment* e) {
    if (size == capacity) resize();
    a[size++] = e;
}

// Поиск индекса по ID
int Gym::findIndexById(int id) const {
    for (int i = 0; i < size; i++) {
        if (a[i]->getId() == id)
            return i;
    }
    return -1;
}

// Удаление тренажёра
void Gym::deleteEquipment(int id) {
    int idx = findIndexById(id);
    if (idx == -1) {
        cout << "Тренажёр не найден." << endl;
        return;
    }

    delete a[idx];

    for (int i = idx; i < size - 1; i++) {
        a[i] = a[i + 1];
    }

    size--;
    cout << "Тренажёр удален." << endl;
}

void Gym::updateLastId() {
    lastId = 0;
    for (int i = 0; i < size; i++) {
        if (a[i]->getId() > lastId)
            lastId = a[i]->getId();
    }
}
// Редактирование тренажёра
void Gym::editEquipment(int id) {
    int idx = findIndexById(id);
    if (idx == -1) {
        cout << "Тренажёр не найден." << endl;
        return;
    }

    Equipment* e = a[idx];
    string newName = inputString("Введите новое название: ");
    if (!newName.empty()) e->setName(newName);  //проверка на пустоту

    cout << "Отредактировано." << endl;
}

// Сортировка по ID
void Gym::sortById() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (a[i]->getId() > a[j]->getId())
                swap(a[i], a[j]);
        }
    }
    cout << "Отсортировано по ID." << endl;
}

// Поиск по части названия
void Gym::searchByName(const string& part) {
    cout << "Результаты поиска:" << endl;

    for (int i = 0; i < size; i++) {
        if (a[i]->getName() == part) {
            cout << "ID: " << a[i]->getId()
                << ", Название: " << a[i]->getName()
                << ", Производитель: " << a[i]->getManufacturer().getName()
                <<endl;
        }
    }
}

// Просмотр всех тренажёров
void Gym::viewAll() const {
    printTable(*this, cout);
}

// Сохранение в файл
void Gym::saveToFile(const string& filename) const {
    ofstream fout(filename);

    if (!fout.good()) {
        cout << "Ошибка открытия файла." << endl;
        return;
    }

    printTable(*this, fout);

    // Проверка состояния потока
    if (fout.bad()) cout << "Критическая ошибка записи." << endl;
    else if (fout.fail()) cout << "Ошибка форматирования." << endl;
    else if (fout.good()) cout << "Данные успешно записаны." << endl;

    fout.close();
}

// Демонстрация чтения файла
void Gym::loadDemo(const string& filename) {
    ifstream fin(filename);

    if (!fin.good()) {
        cout << "Ошибка открытия файла"<<filename<<"." << endl;
        return;
    }

    string line;

    while (getline(fin, line)) {
        if (fin.bad()) {
            cout << "Критическая ошибка чтения." << endl;
            break;
        }
        if (fin.fail()) {
            if (fin.eof()) cout << "Достигнут конец файла." << endl;
            else cout << "Ошибка форматирования." << endl;
            break;
        }
        cout << line << endl;
    }

    fin.clear();
    fin.close();
}


// Проверка целого числа
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

// Проверка вещественного числа
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

// Ввод строки
string inputString(const char* msg) {
    cout << msg;
    string s;
    getline(cin, s);
    return s;
}


void printTable(const Gym& gym, ostream& os) {

    os.setf(ios::left, ios::adjustfield);
    os.setf(ios::showpoint);
    os.setf(ios::boolalpha);
    os.setf(ios::fixed);
    os.setf(ios::showpos);

    os << setw(6) << "ID"
        << setw(20) << "Название"
        << setw(18) << "Тип"
        << setw(15) << "Параметр 1"
        << setw(15) << "Параметр 2"
        << setw(20) << "Производитель"
        << setw(15) << "Страна"
        << "\n";

    os << setfill('-') << setw(109) << "" << "\n";
    os << setfill(' ');

    for (int i = 0; i < gym.getSize(); i++) {

        Equipment* e = gym.getAt(i);

        os << setw(6) << e->getId()
            << setw(20) << e->getName()
            << setw(18) << e->getType()
            << setw(15) << e->getParam1()
            << setw(15) << e->getParam2()
            << setw(20) << e->getManufacturer().getName()
            << setw(15) << e->getManufacturer().getCountry()
            << "\n";
    }

    os.unsetf(ios::showpos);
    os.unsetf(ios::boolalpha);
}


