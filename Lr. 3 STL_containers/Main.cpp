#include "BankSystem.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    clearScreen();

    OperationManager<vector<BankTransaction>> corporateManager;
    OperationManager<list<BankTransaction>> retailManager;

    DepositAccount depAcc("BY99UNBS31300000000000009999", "Смирнов А.С.", 9.5);
    BankTransaction sampleTrans(1, 15000.00, "16.10.2026", depAcc);
    BankBranch branch("Главное отделение МТБ-Банка (Минск)", &sampleTrans);

    int mainChoice = -1;
    while (mainChoice != 0) {
        setColor(11); 
        cout << "\n===========================================================\n";
        setColor(13);
        cout << "  АВТОМАТИЗИРОВАННАЯ БАНКОВСКАЯ СИСТЕМА                   \n";
        setColor(11);
        cout << "===========================================================\n";
        setColor(13);
        cout << "1 - Реестр операций физических лиц\n";
        cout << "2 - Реестр операций юридических лиц\n";
        cout << "3 - Ежедневные операции в банке\n";
        setColor(12); 
        cout << "0 - Выйти из банковской системы\n";
        setColor(7);

        mainChoice = inputInt("Ваш выбор: ");

        switch (mainChoice) {
        case 1:
            runDynamicMenu(retailManager, "ОПЕРАЦИИ ФИЗИЧЕСКИХ ЛИЦ", false, branch);
            break;
        case 2:
            runDynamicMenu(corporateManager, "КОРПОРАТИВНЫЕ ПЛАТЕЖИ", true, branch);
            break;
        case 3:
            runArrayMenu();
            break;
        case 0:
            setColor(10);
            cout << "До свидания!\n";
            setColor(7);
            break;
        default:
            setColor(12);
            cout << "Ошибка! Команда с таким номером отсутствует.\n";
            setColor(7);
            break;
        }
    }

    return 0;
}