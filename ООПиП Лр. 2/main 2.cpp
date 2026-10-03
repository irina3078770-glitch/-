//14. Создать класс Array для работы с двумерными массивами (как
//целочисленными, так и дробными).Найти наибольший элемент массива,
//который кратен двум.Найти сумму номеров минимального и максимального
//элементов массива.Память под массив выделять динамически.Размер
//массива указывает пользователь.Необходимо обязательно освобождать
//память, выделенную под массив.Написать свой манипулятор, выводящий
//содержимое массива в табличном виде.

#include<iostream>
#include"Header 2.h"

using namespace std;

int main() {
	setlocale(0, "rus");
	int count = 0;
	int current = -1;
	Array** a = new Array * [10];
	while (1) {
		switch (menu()) {
		case 1: {
			int r, c;
			
			do {
				cout << "Введите количество строк" << endl;
				while (true) {
					if (cin >> r) {
						// Успешный ввод
						if (cin.peek() != '\n' && cin.peek() != ' ' && !cin.eof()) {
							// есть лишние символы
							std::cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cout << "Ошибка! Введите целое число!\n";
							continue;
						}
						break;
					}
					else {
						// Ошибка: введено не число
						std::cout << "Ошибка! Числа должны быть целыми\n";
						std::cin.clear(); // сброс флага ошибки
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера
					}
				}
				if (r <= 0) cout << "Ошибка! число должно быть положительным!" << endl;
			} while (r <= 0);
			do {
				cout << "Введите количество столбцов" << endl;
				while (true) {
					if (cin >> c) {
						// Успешный ввод
						if (cin.peek() != '\n' && cin.peek() != ' ' && !cin.eof()) {
							// есть лишние символы
							std::cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cout << "Ошибка! Введите целое число!\n";
							continue;
						}
						break;
					}
					else {
						// Ошибка: введено не число
						std::cout << "Ошибка! Числа должны быть целыми\n";
						std::cin.clear(); // сброс флага ошибки
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера
					}
				}
				if (c <= 0) cout << "Ошибка! число должно быть положительным!" << endl;
			} while (c <= 0);
			a[count] = new Array(r, c);
			a[count]->input();
			current = count;
			count++;
			cout << "Массив создан!" << endl;
			break;
		}

		case 2: {
			if (count == 0) {
				cout << "Нет созданных массивов" << endl;
				break;
			}
			int n;
			cout << "Добавлено " << count << " массив(ов)." << endl;
			do {
				cout << "Выберите номер массива : ";
				while (true) {
					if (cin >> n) {
						// Успешный ввод
						if (cin.peek() != '\n' && cin.peek() != ' ' && !cin.eof()) {
							// есть лишние символы
							std::cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cout << "Ошибка! Введите целое число!\n";
							continue;
						}
						break;
					}
					else {
						// Ошибка: введено не число
						std::cout << "Ошибка! Числа должны быть целыми\n";
						std::cin.clear(); // сброс флага ошибки
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера
					}
				}
				if (n<1 || n> count ) {
					cout << "\nОшибка! Массива с таким номером нет! Повторите попытку"<<endl;
				}
			} while (n<1 || n> count );
			current = n-1;
			cout << "Выбран массив #" << n << endl;
			break;
		}
		case 3: {
			if (current == -1) {
				cout << "Сначала выберите номер массива" << endl;
				break;
			}
			Array* arr = a[current];
			cout << "---Массив #" << current + 1 << "---" << endl;
			for (int i = 0; i < arr->getrows(); i++) {
				for (int j = 0; j < arr->getcols(); j++) {
					cout << table << arr->get(i, j);
				}
				cout << endl;
			}
			break;
		}
		case 4: {
			if (current == -1) {
				cout << "Сначала выберите номер массива" << endl;
				break;
			}
			if (a[current]->max() != 0) {
				cout << "Наибольший элемент, кратный 2 = " << a[current]->max() << endl;
			}
			break;
		}
		case 5: {
			if (current == -1) {
				cout << "Сначала выберите номер массива" << endl;
				break;
			}
			cout << "Сумма индексов минимального и максимального элементов = " << a[current]->sum() << endl;
			break;
		}
		case 6: {
			if (!a || count == 0) {
				cout << "Массив пуст\n";
				break;
			}
			ofstream fout("file2.txt");
			if (!fout) {
				cout << "Ошибка при открытии файла для записи\n";
				break;
			}
			for (int i = 0; i < count; i++) {
				fout << "Объект #" << i + 1 << ", " << a[i]->getrows() << " строк(и), " << a[i]->getcols() << " столбцов(а)\n";
				fout << table;
			    a[i]->savetofile(fout);
			}
			cout << "Данные сохранены в файл\n";
			break;
		}
		case 0: {
			cout << "До свидания!";
			for (int i = 0; i < count; i++) {
				delete a[i];
			}
			delete [] a;
			return 0;
		}
		}
	}
}