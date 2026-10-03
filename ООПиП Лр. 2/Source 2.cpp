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

Array::Array() : rows(0), cols(0), a(nullptr) {};

Array::Array(int r, int c) : rows(r), cols(c) {
	a = new double* [rows];
	for (int i=0; i < rows; i++) {
		a[i] = new double [cols];
	}
}

Array::Array(const Array& obj) {
	rows = obj.rows;
	cols = obj.cols;
	a = new double* [rows];
	for (int i = 0; i < rows; i++) {
		a[i] = new double[cols];
		for (int j = 0; j < cols; j++) {
			a[i][j] = obj.a[i][j];
		}
	}
}

bool Array::setrows(int r) {
	if (r <= 0) return false;
	rows = r;
	return true;
}

bool Array::setcols(int c) {
	if (c <= 0) return false;
	cols = c;
	return true;
}

bool Array::setelements(int r, int c, double value) {
	if (r < 0 || r >= rows || c < 0 || c <= cols) return false;
	a[r][c] = value;
	return true;
}

Array::~Array() {
	if (a != nullptr) {
		for (int i = 0; i < rows; i++) {
			delete[] a[i];
		}
		delete[] a;
	}
}

void Array::input() {
	cout << "Введите элементы массива (" << rows << " строк(и), " << cols << " столбцов(а)\n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << "Элемент [" << i + 1 << "][" << j + 1 << "]: ";
			while (true) {
				if (cin >> a[i][j]) {
					// Успешный ввод
					if (cin.peek() != '\n' && cin.peek() != ' ' && !cin.eof()) {
						// есть лишние символы
						std::cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "Ошибка! Введите число!\n";
						continue;
					}
					break;
				}
				else {
					// Ошибка: введено не число
					std::cout << "Ошибка! Введите число\n";
					std::cin.clear(); // сброс флага ошибки
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера
				}
			}

		}
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера
}


void Array::savetofile(ofstream& fout) const {
	if (rows == 0 || cols == 0 || !a) {
		cout << "Массив пуст!" << endl;
		return;
	}
	fout << "Массив: \n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fout << a[i][j] << "\t";
		}
		fout << endl;
	}
	fout << endl;
}

double Array::max() const {
	double max = 0;
	bool two = false;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (fmod(a[i][j], 2.0) == 0) {
					if (!two || a[i][j] > max) {
						max = a[i][j];
						two = true;
					}
				}
					
			}
		}
	if (!two) {
		cout << "Нет элемента, который делиться на 2!" << endl;
		return 0;
	}
	return max;
}

double Array::sum() const {
	double min = a[0][0], max = a[0][0];
	int indexr1=0, indexc1=0, indexr2=0, indexc2=0, s=0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (a[i][j] < min) {
				min = a[i][j];
				indexr1 = i;
				indexc1 = j;
			}
			 
			if (a[i][j] > max) {
				max = a[i][j];
				indexr2 = i;
				indexc2 = j;
			}
		}
	}
	s = indexr1 + indexc1 + indexr2 + indexc2+4;
	return s;
}

ostream& table(ostream& stream) {
	stream << setprecision(4) << setw(9) << left;
	return stream;
}

int menu() {
	int num;
	cout << "---МЕНЮ---" << endl;
	cout << "1 - Создать новый массив" << endl;
	cout << "2 - Выбрать массив" << endl;
	cout << "3 - Вывести выбранный массив" << endl;
	cout << "4 - Найти наибольший элемент массива, кратный 2" << endl;
	cout << "5 - Найти сумму индексов минимального и максимального элементов" << endl;
	cout << "6 - Записать данные в файл" << endl;
	cout << "0 - Выход" << endl;
	cout << "Ваш выбор: ";
	while (true) {
		if (cin >> num) {
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
			std::cout << "Ошибка! Числа должны быть целыми, повторите ввод\n";
			std::cin.clear(); // сброс флага ошибки
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера
		}
	}
	if (num > 7 || num < 0) {
		cout << "Ошибка! Нет такого номера! Повторите попытку." << endl;
		return -1;
	}
	else return num;
}
