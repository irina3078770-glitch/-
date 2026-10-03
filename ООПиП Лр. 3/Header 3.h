//Реализовать класс Point, описывающий точку на координатной
//плоскости.В классе создать два поля координат x, y.Реализовать в классе
//конструкторы(по умолчанию, с параметрами, копирования), деструктор.
//Создать методы доступа к полям класса.Создать два перегруженных
//оператора « + » и « - » для реализации возможности перемещения точки на
//координатной плоскости.Реализовать friend - функции для операторов
//ввода / вывода в поток для созданного класса.

#pragma once
#include <iostream>

using namespace std;

class Point {
private: 
	double x, y;
public:
	Point();
	Point(double x, double y);
	Point(const Point& obj);

	~Point();

	void setX(double x);
	void setY(double y);
	double getX() const;
	double getY() const;

	Point operator +(const Point& obj);
	Point operator -(const Point& obj);

	friend ostream& operator << (ostream& os, const Point& p);
	friend istream& operator >>(istream& is, Point& p);
};
int menu();
