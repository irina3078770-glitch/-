#include "BankSystem.h"

int main(int argc, char* argv[]) {
    system("chcp 1251 > nul");
    srand(static_cast<unsigned int>(time(nullptr)));

    int choice = 0;
    do {
        setColor(11);
        cout << "\n=========================================\n";
        cout << "           ÁÀÍÊÎÂÑÊÎÅ ÌÅÍÞ              \n";
        cout << "=========================================\n";
        setColor(7);
        cout << " " << setw(2) << left << "1." << " Î×ÅÐÅÄÜ ÏËÀÒÅÆÅÉ\n"
            << " " << setw(2) << left << "2." << " ÈÑÒÎÐÈß ÏËÀÒÅÆÅÉ\n"
            << " " << setw(2) << left << "3." << " ÊÐÅÄÈÒÛ\n";
        setColor(11);
        cout << "-----------------------------------------\n";
        setColor(7);
        cout << " " << setw(2) << left << "0." << " ÂÛÕÎÄ\n";
        setColor(11);
        cout << "=========================================\n";
        setColor(7);

        choice = inputInt("Âûáîð: ");

        switch (choice) {
        case 1:
            QueueMenu();
            break;
        case 2:
            StackMenu();
            break;
        case 3:
            PriorityQueueMenu();
            break;
        case 0:
            setColor(10);
            cout << "\nÄî ñâèäàíèÿ!\n";
            setColor(7);
            break;
        default:
            setColor(12);
            cout << "\nÎøèáêà! Íåâåðíûé âûáîð.\n";
            setColor(7);
        }
    } while (choice != 0);

    return 0;
}