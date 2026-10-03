/* 1. создать программу на языке С/С++, которая позволяет выбрать
номер лабораторной работы семестра (1, 2, 3, 4…),
2. создать массив объектов указанных классов,
3. считать данные объектов с клавиатуры
4. вывести данные объектов на экран и в файл
5. создать методы установки значений полей класса. Методы
должны проверять корректность задаваемых параметров
6. создать конструктор с параметрами, конструктор без
параметров, конструктор копирования, деструктор.
14. Создать класс TwoDimensionalArray (двумерный массив), в котором
реализовать методы для работы с двумерными массивами: метод поиска
минимального элемента ниже главной диагонали; метод поиска
максимального элемента выше главной диагонали. Память под массивы
выделять динамически. Деструктор должен освобождать память,
выделенную под массивы.
*/

#include<iostream>
#include<fstream>
#include"Header 1.h"

using namespace std;

int main()
{
	setlocale(0, "rus");
	TwoDimensionalArray* a = nullptr;
	int n = 0;
	bool minzn = false;
	bool maxzn = false;
	while (1)
	{
		switch (menu())
		{
		case 1:
		{
			if (a) {
				delete[] a;
				a = nullptr;
			}
			do {
				cout << "Введите количество объектов массива: ";
				while (true) {
					if (cin >> n) {
						// Успешный ввод
						if (cin.peek() != '\n' && cin.peek() != ' ' && !cin.eof()) {
							// есть лишние символы
							std::cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cout << "Ошибка! Введите целое число без дополнительных символов.\n";
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
				if (n <= 0) cout << "Ошибка! Количество должно быть > 0";
			} while (n <= 0);
			a = new TwoDimensionalArray[n];
			for (int i = 0; i < n; i++) {
				int r, c;
				cout << "Объект # " << i + 1 << endl;
				cout << "Введите количество строк и столбцов: ";
				do {
					while (true) {
						if (cin >> r >> c) {
							// Успешный ввод
							if (cin.peek() != '\n' && cin.peek() != ' ' && !cin.eof()) {
								// есть лишние символы
								std::cin.clear();
								cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								std::cout << "Ошибка! Введите целое число без дополнительных символов.\n";
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
					if (r <= 0 || c <= 0) cout << "Ошибка! Числа должны быть > 0";
				} while (r <= 0 || c <= 0);
				a[i].setSize(r, c);
				a[i].allocMemory();
				a[i].input();
			}
			break;
		}
		case 2: {
			if (!a || n == 0) {
				cout << "Массив пуст\n";
				break;
			}
			for (int i = 0; i < n; i++) {
				cout << "Объект #" << i + 1 << ", " << a[i].getRows() << " строк(и), " << a[i].getCols() << " столбцов(а)\n";
				a[i].output();
			}
			break;
		}
		case 3: {
			if (!a || n == 0) {
				cout << "Массив пуст\n";
				break;
			}
			ofstream fout ("file.txt");
			if (!fout) {
				cout << "Ошибка при открытии файла для записи\n";
				break;
			}
			for (int i = 0; i < n; i++) {
				fout << "Объект #" << i + 1 << ", " << a[i].getRows() << " строк(и), " << a[i].getCols() << " столбцов(а)\n";
				a[i].saveToFile(fout);
				if (minzn) fout << "Минимум ниже главной диагонали в массиве " << i + 1 << " = " << a[i].min() << "\n";
				if (maxzn) fout << "Максимальный элемент выше главной диагонали в массиве " << i + 1 << " = " << a[i].max() << "\n";
			}
			cout << "Данные сохранены в файл\n";
			break;
		}
		case 4: {
			if (!a || n == 0) {
				cout << "Массив пуст\n";
			}
			for (int i = 0; i < n; i++) {
				int min = a[i].min();
				cout << "Минимум ниже главной диагонали в массиве "<<i+1<<" = " << min<<"\n";
			}
			minzn = true;
			break;
		}
		case 5: {
			if (!a || n == 0) {
				cout << "Массив пуст\n";
			}
			for (int i = 0; i < n; i++) {
				int max = a[i].max();
				cout << "Максимальный элемент выше главной диагонали в массиве " << i + 1 << " = " << max << "\n";
			}
			maxzn = true;
			break;
		}
		case 6: return 0;

		}
	}
}