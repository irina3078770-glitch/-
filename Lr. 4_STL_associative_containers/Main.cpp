#include "BankOperations.h"

void printMenu() {
    setColor(CLR_MAGENTA);
    cout << "\n====================================================================\n";
    cout << "               БАНКОВСКАЯ СИСТЕМА УЧЕТА ОПЕРАЦИЙ                    \n";
    cout << "====================================================================\n";
    setColor(CLR_DEFAULT);
    cout << "1 - Провести новую операцию \n";
    cout << "2 - Удалить операцию по ID\n";
    cout << "3 - Редактировать данные операции по ID\n";
    cout << "4 - Найти операцию по ID\n";
    cout << "5 - Фильтрация операций по минимальной сумме\n";
    cout << "--------------------------------------------------------------------\n";
    setColor(CLR_CYAN);
    cout << "ОТЧЕТЫ И ПРОСМОТР ДАННЫХ:\n";
    setColor(CLR_DEFAULT);
    cout << "6 - Показать все операции \n";                              // map
    cout << "7 - Показать уникальные клиентские счета\n";                // set
    cout << "8 - Показать историю операций по счетам\n";                 // multimap
    cout << "9 - Показать отсортированные суммы операций\n";             // multiset
    cout << "10 - Показать быстрый реестр операций по ID\n";             // unordered_map
    cout << "11 - Показать список проверенных счетов\n";                 // unordered_set;
    cout << "12 - Показать группировку операций по типам\n";             // unordered_multimap
    cout << "13 - Показать все комиссии банка\n";                        // unordered_multiset
    cout << "--------------------------------------------------------------------\n";
    cout << "15 - Сохранить данные в файл\n";
    cout << "16 - Загрузить данные из файла\n";
    cout << "0 -  ВЫХОД\n";
    setColor(CLR_MAGENTA);
    cout << "====================================================================\n";
    setColor(CLR_DEFAULT);
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    BankManager manager;
    string filename = "bank_data.txt";

    manager.addTransaction(BankTransaction(0, "BY13OLMP3812", "Перевод", 1500.0, 15.0));
    manager.addTransaction(BankTransaction(0, "BY20BABB3014", "Снятие", 200.0, 2.0));
    manager.addTransaction(BankTransaction(0, "BY13OLMP3812", "Пополнение", 5000.0, 0.0));

    while (true) {
        printMenu();
        int choice = BankManager::inputInt("Ваш выбор: ");

        switch (choice) {
        case 1: {
            BankTransaction tx;
            tx.inputData();
            manager.addTransaction(tx);
            break;
        }
        case 2: {
            int id = BankManager::inputInt("Введите ID для удаления: ");
            manager.removeTransaction(id);
            break;
        }
        case 3: {
            int id = BankManager::inputInt("Введите ID для редактирования: ");
            manager.editTransaction(id);
            break;
        }
        case 4: {
            int id = BankManager::inputInt("Введите ID для поиска: ");
            manager.searchById(id);
            break;
        }
        case 5: {
            double minAmt = BankManager::inputDouble("Введите минимальную сумму операции: ");
            manager.filterByAmount(minAmt);
            break;
        }
        case 6:  manager.displayAllMap(); break;           // map
        case 7:  manager.displayAllSet(); break;           // set
        case 8:  manager.displayAllMultiMap(); break;      // multimap
        case 9:  manager.displayAllMultiSet(); break;      // multiset
        case 10: manager.displayAllUnorderedMap(); break;  // unordered_map
        case 11: manager.displayAllUnorderedSet(); break;  // unordered_set
        case 12: manager.displayAllUnorderedMultiMap(); break; // unordered_multimap
        case 13: manager.displayAllUnorderedMultiSet(); break; // unordered_multiset
        case 14:
            manager.displayAllMap();
            manager.displayAllSet();
            manager.displayAllMultiMap();
            manager.displayAllMultiSet();
            manager.displayAllUnorderedMap();
            manager.displayAllUnorderedSet();
            manager.displayAllUnorderedMultiMap();
            manager.displayAllUnorderedMultiSet();
            break;
        case 15: manager.saveToFile(filename); break;
        case 16: manager.loadFromFile(filename); break;
        case 0:
            setColor(CLR_GREEN);
            cout << "До свидания!\n";
            setColor(CLR_DEFAULT);
            return 0;
        default:
            setColor(CLR_RED);
            cout << "Неверный пункт меню!\n";
            setColor(CLR_DEFAULT);
        }
    }
}