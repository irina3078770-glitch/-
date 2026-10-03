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

using namespace std;


class TwoDimensionalArray {
private:
	int rows;
	int cols;
	int** t;
	void freeMemory() {
		if (t) {
			for (int i = 0; i < rows; i++) {
				delete[] t[i];
			}
			delete[] t;
			t = nullptr;
		}
	}
public:
	//конструктор без параметров
	TwoDimensionalArray() : rows(0), cols(0), t(nullptr) {}

	//конструктор с параметрами
	TwoDimensionalArray(int r, int c) {
		setSize(r, c);
		allocMemory();
	}
	//конструктор копирования
	TwoDimensionalArray(const TwoDimensionalArray& obj) {
		rows = obj.rows;
		cols = obj.cols;
		allocMemory();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				t[i][j] = obj.t[i][j];
			}
		}
	}
	//деструктор
	~TwoDimensionalArray() {
		freeMemory();
	}
	//установка размера 
	bool setSize(int r, int c) {
		if (r <= 0 || c <= 0) {
			cout << "Ошибка! Размеры должны быть положительными числами\n";
			return false;
		}
		rows = r;
		cols = c;
		return true;
	}
	//выделение памяти
	void allocMemory() {
		freeMemory();
		t = new int* [rows];
		for (int i = 0; i < cols; i++) {
			t[i] = new int[cols];
		}
	}
	//меню
	static int menu() {
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
	//ввод массива
	void input() {

		cout << "Введите элементы массива (" << rows << " строк(и), " << cols << " столбцов(а)\n";
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << "Элемент [" << i + 1 << "][" << j + 1 << "]: ";
				while (true) {
					if (cin >> t[i][j]) {
						// Успешный ввод
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
	}
	//вывод массива
	void output() {
		if (rows == 0 || cols == 0 || !t) {
			cout << "Массив пуст!" << endl;
			return;
		}
		cout << "Массив: \n";
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << t[i][j] << "\t";
			}
			cout << endl;
		}
	}
	//запись в файл
	void saveToFile(ofstream& fout) const {
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
	//минимум ниже гланой диагонали
	int min() const {
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
	//максимум выше главной диагонали
	int max() const {
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
	int getRows() const {
		return rows;
	}
	int getCols() const {
		return cols;
	}
};

int main()
{
	setlocale(0, "rus");
	TwoDimensionalArray* a = nullptr;
	int n = 0;
	bool minzn = false;
	bool maxzn = false;
	while (1)
	{
		switch (TwoDimensionalArray::menu())
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
			ofstream fout("file.txt");
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
				cout << "Минимум ниже главной диагонали в массиве " << i + 1 << " = " << min << "\n";
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