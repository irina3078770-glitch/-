#include "BankOperations.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned int>(time(NULL)));

    string dataFile = "bank_operations.txt";

    // ПАТТЕРН 3: ФАБРИЧНЫЙ КОНСТРУКТОР - регистрация всех 5 типов операций в динамическом реестре
    DepositOperation::Register();
    WithdrawalOperation::Register();
    TransferOperation::Register();
    UtilityPaymentOperation::Register();
    CurrencyExchangeOperation::Register();

    vector<unique_ptr<BankOperation> > operations;

    int choice = 0;
    do {
        setColor(11);
        cout << "\n==================== УЧЕТ ВЫПОЛНЯЕМЫХ БАНКОВСКИХ ОПЕРАЦИЙ ====================\n";
        setColor(7);
        cout << "1. Добавить банковскую операцию\n";
        cout << "2. Удалить банковскую операцию по ID\n";
        cout << "3. Редактировать банковскую операцию по ID\n";
        cout << "4. Вывести все операции и документы на экран\n";
        cout << "5. Сохранить операции в файл (" << dataFile << ")\n";
        cout << "6. Загрузить операции из файла (" << dataFile << ")\n";
        cout << "0. Выход из программы\n";

        choice = inputInt("Выберите пункт меню: ");

        switch (choice) {
        case 1:
            addOperationMenu(operations);
            break;
        case 2:
            deleteOperationById(operations);
            break;
        case 3:
            editOperationById(operations);
            break;
        case 4:
            displayAllOperations(operations);
            break;
        case 5:
            saveOperationsToFile(operations, dataFile);
            break;
        case 6:
            loadOperationsFromFile(operations, dataFile);
            break;
        case 0:
            setColor(10);
            cout << "\nДо свидания!\n";
            setColor(7);
            break;
        default:
            setColor(12);
            cout << "Ошибка! Введите пункт меню от 0 до 6.\n";
            setColor(7);
            break;
        }
    } while (choice != 0);
    return 0;
}