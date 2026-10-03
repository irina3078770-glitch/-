#include "Shop.h"

using namespace std;

int inputInt(const char* msg) {
    int v;
    while (true) {
        cout << msg;
        if (cin >> v && (cin.peek() == '\n' || cin.peek() == ' ')) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        cout << "Ошибка! Введите целое число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double inputDouble(const char* msg) {
    double v;
    while (true) {
        cout << msg;
        if (cin >> v && (cin.peek() == '\n' || cin.peek() == ' ')) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        cout << "Ошибка! Введите число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
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

ostream& operator<<(ostream& os, const BuildingMaterial& mat) {
    mat.printData();
    return os;
}

istream& operator>>(istream& is, BuildingMaterial& mat) {
    mat.inputData();
    return is;
}


void BuildingMaterial::inputData() {
    inputString(name, 50, "Наименование: ");
    price = inputDouble("Цена: ");
}

void BuildingMaterial::printData() const {
    cout << "Наименование: " << setw(18) << left << name << " | Цена: " << setw(7) << price;
}

void DryMix::inputData() {
    BuildingMaterial::inputData();
    weightKg = inputDouble("Вес упаковки (кг): ");
}

void DryMix::printData() const {
    cout << "Сухая смесь: ";
    BuildingMaterial::printData();
    cout << " | Вес: " << weightKg << " кг";
}

void Paint::inputData() {
    BuildingMaterial::inputData();
    inputString(color, 30, "Цвет: ");
}

void Paint::printData() const {
    cout << "Краска:    ";
    BuildingMaterial::printData();
    cout << " | Цвет: " << color;
}


Material OrderItem::pack() const {
    Material data{};
    if (!material) return data;

    data.type = material->getType();
    strcpy_s(data.name, material->getName());
    data.price = material->getPrice();
    data.stock = material->getStock(); 
    data.quantity = quantity;
    data.weightKg = material->getWeightKg();
    strcpy_s(data.color, material->getColor());

    return data;
}

// Восстановление из класса Material
void OrderItem::unpack(const Material& data) {
    delete material;
    quantity = data.quantity;

    if (data.type == dryMix) {
        material = new DryMix(data.name, data.price, data.weightKg, data.stock);
    }
    else if (data.type == paint) {
        material = new Paint(data.name, data.price, data.color, data.stock);
    }
}

void OrderManager::checkStreamState(const ios& stream, const char* op) const {
    if (stream.bad()) cerr << "Ошибка badbit: " << op << endl;
    if (stream.fail() && !stream.eof()) cerr << "Ошибка failbit: " << op << endl;
}

int OrderManager::getRecordCount() const {
    ifstream f(fileName, ios::binary | ios::ate);
    return f ? static_cast<int>(f.tellg() / sizeof(Material)) : 0;
}

void OrderManager::addRecord() {
    Catalog catalog;
    catalog.displayCatalog();

    int choice = inputInt("Выберите номер товара (0 - отмена): ");
    if (choice == 0) return;

    if (choice < 1 || choice > catalog.getCount()) {
        cout << "Ошибка! Товара с таким номером нет в каталоге.\n";
        return;
    }

    int index = choice - 1;
    BuildingMaterial* selectedItem = catalog.getItem(index);

    int qty = inputInt("Введите количество для заказа: ");

    if (qty <= 0) {
        cout << "Ошибка! Количество должно быть больше 0.\n";
        return;
    }

    if (qty > selectedItem->getStock()) {
        cout << "Ошибка! На складе недостаточно товара.\n"
            << "Доступно для заказа: " << selectedItem->getStock() << " шт.\n";
        return;
    }

    BuildingMaterial* mat = catalog.createCopy(index);
    OrderItem item(mat, qty);
    Material data = item.pack();

    ofstream f(fileName, ios::binary | ios::app);
    if (!f) {
        cout << "Ошибка открытия файла записи!\n";
        delete mat;
        return;
    }

    f.write(reinterpret_cast<char*>(&data), sizeof(data));
    checkStreamState(f, "Добавление");

    if (f.good()) {
        cout << "Товар успешно добавлен в заказ!\n";
    }
}

void OrderManager::displayAll() const {
    ifstream f(fileName, ios::binary);
    if (!f) { 
        cout << "Файл пуст или не существует.\n";
        return; 
    }

    Material data;
    int idx = 1;
    double total = 0;
    cout << "\n================ СОСТАВ ЗАКАЗА ================\n";
    while (f.read(reinterpret_cast<char*>(&data), sizeof(data))) {
        OrderItem item;
        item.unpack(data);
        cout << idx++ << ". ";

        // Перегруженный оператор <<
        cout << *(item.getMaterial());

        cout << " | Кол-во: " << item.getQuantity() << " | Итого: " << item.getTotalCost() << " руб.\n";
        total += item.getTotalCost();
    }
    checkStreamState(f, "Чтение");
    cout << "\nИТОГО: " << total << " руб.\n===============================================\n";
}


void OrderManager::editRecord(int index) {
    if (index < 1 || index > getRecordCount()) {
        cout << "Неверный номер.\n";
        return;
    }

    fstream f(fileName, ios::binary | ios::in | ios::out);
    if (!f.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

 
    f.seekg((index - 1) * sizeof(Material));
    Material data;
    f.read(reinterpret_cast<char*>(&data), sizeof(data));

    OrderItem item;
    item.unpack(data);

    int newQty = inputInt("Новое количество (0 - отмена): ");
    if (newQty <= 0) {
        f.close();
        return;
    }

    if (newQty > item.getMaterial()->getStock()) {
        cout << "Ошибка: на складе всего " << item.getMaterial()->getStock() << " шт.\n";
        f.close();
        return;
    }

    data.quantity = newQty;

    f.clear();
    f.seekp((index - 1) * sizeof(Material));
    f.write(reinterpret_cast<char*>(&data), sizeof(data));
    f.flush();

    if (f.good()) {
        cout << "Обновлено!\n";
    }
    else {
        cout << "Ошибка записи в файл!\n";
    }

    f.close();
}
void OrderManager::deleteRecord(int index) {
    if (index < 1 || index > getRecordCount()) { 
        cout << "Неверный номер.\n";
        return; 
    }

    ifstream in(fileName, ios::binary);
    ofstream out("temp.dat", ios::binary);
    Material data;
    int curr = 1;

    while (in.read(reinterpret_cast<char*>(&data), sizeof(data))) {
        if (curr++ != index) out.write(reinterpret_cast<char*>(&data), sizeof(data));
    }
    in.close(); 
    out.close();
    remove(fileName);
    rename("temp.dat", fileName);
    cout << "Запись удалена.\n";
}

void OrderManager::searchByName(const char* query) const {
    ifstream f(fileName, ios::binary);
    if (!f) return;
    Material data;
    bool found = false;

    while (f.read(reinterpret_cast<char*>(&data), sizeof(data))) {
        if (strstr(data.name, query)) {
            OrderItem item;
            item.unpack(data);
            cout << *(item.getMaterial()) << " | Кол-во: " << item.getQuantity() << endl;
            found = true;
        }
    }
    if (!found) cout << "Ничего не найдено.\n";
}

