#include<iostream>
#include<fstream>
#include"Header 1.h"

using namespace std;

bool TwoDimensionalArray::setSize(int r, int c) {

	if (r <= 0 || c <= 0) {
		cout << "Ошибка! Размеры должны быть положительными числами\n";
		return false;
	}
	rows = r;
	cols = c;
	return true;
}
void TwoDimensionalArray::allocMemory() {
	freeMemory();
	t = new int* [rows];
	for (int i = 0; i < rows; i++) {
		t[i] = new int[cols];
	}
}
int menu() {
	int v;
	cout << "Меню:\n";
	cout << "1 - добавить массив объектов\n";
	cout << "2 - вывести массив объектов \n";
	cout << "3 - сохранить массив объектов в файл\n";
	cout << "4 - найти минимум ниже главной диагонали\n";
	cout << "5 - найти максимум выше главной диагонали\n";
	cout << "6 - выход\n";
	cout << "Ваш выбор? ";
	while (true) {
		if (cin >> v) {
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
	if (v < 1 || v > 6) {
		cout << "Такой команды нет\n";
		return -1;
	}
	else return v;
}
void TwoDimensionalArray::input() {

	cout << "Введите элементы массива (" << rows << " строк(и), " << cols << " столбцов(а)\n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << "Элемент [" << i + 1 << "][" << j + 1 << "]: ";
			while (true) {
				if (cin >> t[i][j]) {
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

		}
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера
}
void TwoDimensionalArray::output() {
	if (rows == 0 || cols == 0 || !t) {
		cout << "Массив пуст!" << endl;
		return;
	}
	cout << "---Массив--- \n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << t[i][j] << "\t";
		}
		cout << endl;
	}
}
void TwoDimensionalArray::saveToFile(ofstream& fout) const {
	if (rows == 0 || cols == 0 || !t) {
		cout << "Массив пуст!" << endl;
		return;
	}
	fout << "Массив: \n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fout << t[i][j] << "\t";
		}
		fout << endl;
	}
	fout << endl;
}
int TwoDimensionalArray::min() const {
	int min;

	if (rows < 2 || cols < 2) {
		cout << "Размер массива не позволяет найти минимум ниже главной диагонали.\n";
		return 0;
	}
	min = t[1][0];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < i && j < cols; j++) {
			if (t[i][j] < min) min = t[i][j];
		}
	}
	return min;
}
int TwoDimensionalArray::max() const {
	int max;
	if (rows < 2 || cols < 2) {
		cout << "Размер массива не позволяет найти максимум выше главной диагонали.\n";
		return 0;
	}
	max = t[0][1];
	for (int i = 0; i < rows; i++) {
		for (int j = i + 1; j < cols; j++) {
			if (t[i][j] > max) max = t[i][j];
		}
	}
	return max;
}
int TwoDimensionalArray::getRows() const {
	return rows;
}
int TwoDimensionalArray::getCols() const {
	return cols;
};