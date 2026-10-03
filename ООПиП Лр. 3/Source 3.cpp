//Реализовать класс Point, описывающий точку на координатной
//плоскости.В классе создать два поля координат x, y.Реализовать в классе
//конструкторы(по умолчанию, с параметрами, копирования), деструктор.
//Создать методы доступа к полям класса.Создать два перегруженных
//оператора « + » и « - » для реализации возможности перемещения точки на
//координатной плоскости.Реализовать friend - функции для операторов
//ввода / вывода в поток для созданного класса.

#include <iostream>
#include"header 3.h"

using namespace std;

Point::Point() : x(0), y(0) {};
Point::Point(double x, double y) :x(x), y(y) {};
Point::Point(const Point& obj) : x(obj.x), y(obj.y) {};

Point::~Point() {};

void Point::setX(double x) {
	this->x = x;
}
void Point::setY(double y) {
	this->y = y;
}

double Point::getX() const {
	return x;
}
double Point::getY() const {
	return y;
}

Point Point::operator +(const Point& obj) {
	return Point(x + obj.x, y + obj.y);
}
Point Point::operator -(const Point& obj) {
	return Point(x - obj.x, y - obj.y);
}

ostream& operator <<(ostream& os, const Point& p) {
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}
istream &operator>>(istream &is, Point &p) {
	cout << "Введите x: ";
	is >> p.x;
	cout << "Введите y: ";
	is >> p.y;
	return is;
}

int menu() {
	int v;
	cout << "---Меню---" << endl;
	cout << "0 - Создать точки" << endl;
	cout << "1 - Показать все точки" << endl;
	cout << "2 - Добавить новую точку" << endl;
	cout << "3 - Сложить две точки" << endl;
	cout << "4 - Вычесть две точки" << endl;
	cout << "5 - Выход" << endl;
	cout << "Выш выбор? ";
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
	if (v < 0 || v>5) {
		cout << "Ошибка! Нет такого числа" << endl;
		return -1;
	}
	return v;
}