#include<iostream>
#include<windows.h>
#include"Hospital.h"

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "rus");
	set_terminate(myTerminate);

		Hospital h;
		h.input();

		int choice;
		do {
			cout << "\n1 - Добавить врача\n";
			cout << "2 - Добавить медсестру\n";
			cout << "3 - Добавить техника\n";
			cout << "4 - Показать отделение\n";
			cout << "0 - Выход\n";

			choice = inputInt("Ваш выбор: ");

			try {
				switch (choice) {
				case 1: h.addDoctor(); break;
				case 2: h.addNurse(); break;
				case 3: h.addTech(); break;
				case 4: h.print(); break;
				case 0: cout << "До свидания!\n"; break;
				default: cout << "Неверный пункт меню!\n";
				}
			}
			catch (const StaffException& e) {
				cout << "Ошибка: " << e.what() << "\n";
			}
			catch (const char* msg) {
				cout << "Ошибка: " << msg << "\n";
			}
			catch (int) {
				cout << "Ошибка: неверная смена.\n";
			}
			catch (double) {
				cout << "Ошибка: неверная зарплата.\n";
			}
		} while (choice != 0);

	return 0;
}