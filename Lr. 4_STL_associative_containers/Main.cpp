#include "BankOperations.h"

void printMenu() {
    setColor(CLR_MAGENTA);
    cout << "\n====================================================================\n";
    cout << "       БАНКОВСКАЯ СИСТЕМА УЧЕТА                                       \n";
    cout << "====================================================================\n";
    setColor(CLR_DEFAULT);
    cout << "1 - Провести новую операцию\n";
    cout << "2 - Удалить операцию по ID\n";
    cout << "3 - Редактировать операцию по ID\n";
    cout << "4 - Найти операцию по ID\n";
    cout << "5 - Фильтрация операций по минимальной сумме\n";
    cout << "--------------------------------------------------------------------\n";
    setColor(CLR_CYAN);
    cout << "--------------------------------------------------------------------\n";
    setColor(CLR_DEFAULT);
    cout << "6  - Показать все операции (по ID)\n";         // Использует map
    cout << "7  - Показать список уникальных счетов\n";              // Использует set
    cout << "8  - Показать историю операций по счетам\n";    // Использует multimap
    cout << "9  - Показать отсортированные суммы транзакций\n";      // Использует multiset
    cout << "10 - Показать быстрый реестр операций по ID\n";          // Использует unordered_map
    cout << "11 - Показать базу уникальных счетов\n";         // Использует unordered_set
    cout << "12 - Показать группировку операций по клиентам\n";      // Использует unordered_multimap
    cout << "13 - Показать статистику сумм \n";      // Использует unordered_multiset
    cout << "--------------------------------------------------------------------\n";
    cout << "14 - Сохранить в файл\n";
    cout << "15 - Загрузить из файла\n";
    cout << "0  - ВЫХОД\n";
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
            double minAmt = BankManager::inputDouble("Введите минимальную сумму: ");
            manager.filterByAmount(minAmt);
            break;
        }
        case 6: manager.displayAllMap(); break;
        case 7: manager.displayAllSet(); break;
        case 8: manager.displayAllMultiMap(); break;
        case 9: manager.displayAllMultiSet(); break;
        case 10: manager.displayAllUnorderedMap(); break;
        case 11: manager.displayAllUnorderedSet(); break;
        case 12: manager.displayAllUnorderedMultiMap(); break;
        case 13: manager.displayAllUnorderedMultiSet(); break;
        case 14: manager.saveToFile(filename); break;
        case 15: manager.loadFromFile(filename); break;
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