//Реализовать класс Point, описывающий точку на координатной
//плоскости.В классе создать два поля координат x, y.Реализовать в классе
//конструкторы(по умолчанию, с параметрами, копирования), деструктор.
//Создать методы доступа к полям класса.Создать два перегруженных
//оператора « + » и « - » для реализации возможности перемещения точки на
//координатной плоскости.Реализовать friend - функции для операторов
//ввода / вывода в поток для созданного класса.

#include<iostream>
#include<limits>
#include"header 3.h"

using namespace std;

int main() {
	setlocale(0, "rus");
	Point* points = nullptr;
	int size = 0;
	while (1) {
		switch (menu()) {
		case 0: {
			int n;
			cout << "Введите количество точек: " << endl;
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
			delete [] points;
			points = new Point[n];
			size = n;
			for (int i = 0; i < n; i++) {
				cout << "Введите точку #" << i + 1 << ":" << endl;
				while (true) {
					if (cin >> points[i]) {
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
			cout << "Точки добавлены" << endl;
			break;
		}
		case 1: {
			if (size == 0) {
				cout << "Список пуст" << endl;
			}
			else { 
				cout << "---Список точек---" << endl;
				for (int i = 0; i < size; i++) {
					cout << i+1 << ": " << points[i] << endl;
				}
			}
			break;
		}
		case 2: {
			Point p;
			cout << "Введите новую точку:" << endl;
			while (true) {
				if (cin >> p) {
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
			Point* newPoints = new Point[size + 1];

			for (int i = 0; i < size; i++) {
				newPoints[i] = points[i];
			}
			newPoints[size] = p;
			delete[] points;
			points = newPoints;
			size++;
			cout << "Точка добавлена!" << endl;
			break;
		}
		case 3: {
			if (size < 2) {
				cout << "Недостаточно точек! Нужно минимум две!" << endl;
				break;
			}
			int a, b;
			cout << "Введите индексы двух точек для сложения:" << endl;
			while (true) {
				if (cin >> a>>b) {
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
			a--;
			b--;
			if (a >= 0 && a < size && b >= 0 && b < size) {
				Point c = points[a] + points[b];
				cout << "Результат: " << c << endl;
			}
			else cout << "Неверные индексы" << endl;
			break;
		}
		case 4: {
			if (size < 2) {
				cout << "Недостаточно точек! Нужно минимум две точки!" << endl;
				break;
			}
			int a, b;
			cout << "Введите индексы двух точек для вычитания:" << endl;
			while (true) {
				if (cin >> a>>b) {
					// Успешный ввод
					if (cin.peek() != '\n' && cin.peek() != ' ' && !cin.eof()) {
						// есть лишние символы
						std::cin.clear();
						cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
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
				a--;
				b--;
				if (a >= 0 && a < size && b >= 0 && b < size) {
					Point c = points[a] - points[b];
					cout << "Результат: " << c << endl;
				}
				else cout << "Неверные индексы" << endl;
				break;
		}
		case 5: {
			cout << "До свидания!" << endl;
			delete[] points;
			return 0;
		}
		}
	}
}

