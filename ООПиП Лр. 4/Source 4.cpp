//Создать классы Circle, Square, Triangle, Shape, Oval, Sphere с
//необходимым набором полей и методов. Создать методы нахождения
//площади и объема фигур. Создать массив объектов базового класса и
//заполнить этот массив объектами базового и производных классов. Написать
//программу, которая создает объекты каждого из этих классов, и находит
//фигуру максимальную по площади и по объему, выводит данные о фигурах
//на экран и в файл. Классы должны содержать методы получения и изменения
//значений всех полей. Все поля классов должны быть объявлены с атрибутами
//private или protected.

#include<iostream>
#include<cmath>
#include"Header 4.h"

using namespace std;

Circle::Circle(double r) : Shape("Circle", 1), radius(r) {}
double Circle::getRadius() const { 
	return radius;
}
void Circle::setRadius(double r) { 
	radius = r; 
}
double Circle::area() const {
	return 3,14 * radius * radius;
}
double Circle::volume() const {
	return 0;
}
void Circle::print(ostream& os) const {
	os << "Фигура: Circle" << endl;
	os << "Радиус: " << radius << endl;
}


Square::Square(double s) : Shape("Square", 2), side(s) {}

double Square::getSide() const { 
	return side;
}
void Square::setSide(double s) { 
	side = s;
}
double Square::area() const { 
	return side * side;
}
double Square::volume() const { 
	return 0;
}
void Square::print(ostream& os) const {
	os << "Фигура: Square\n";
	os << "Сторона: " << side << "\n";
}


Triangle::Triangle(double b, double h) : Shape("Triangle", 3), base(b), height(h) {}

double Triangle::getBase() const { 
	return base;
}
double Triangle::getHeight() const { 
	return height; 
}
void Triangle::setBase(double b) { 
	base = b;
}
void Triangle::setHeight(double h) { 
	height = h; 
}
double Triangle::area() const { 
	return 0.5 * base * height;
}
double Triangle::volume() const {
	return 0; 
}
void Triangle::print(ostream& os) const {
	os << "Фигура: Triangle\n";
	os << "Основание: " << base << ", Высота: " << height << "\n";
}


Oval::Oval(double a_, double b_) : Shape("Oval", 4), a(a_), b(b_) {}

double Oval::getA() const { 
	return a; 
}
double Oval::getB() const { 
	return b; 
}
void Oval::setA(double x) {
	a = x;
}
void Oval::setB(double y) { 
	b = y;
}
double Oval::area() const { 
	return 3.14 * a * b; 
}
double Oval::volume() const {
	return 0;
}
void Oval::print(ostream& os) const {
	os << "Фигура: Oval\n";
	os << "Полуоси: a=" << a << ", b=" << b << "\n";
}


Sphere::Sphere(double r) : Shape("Sphere", 5), radius(r) {}

double Sphere::getRadius() const { 
	return radius;
}
void Sphere::setRadius(double r) { 
	radius = r; 
}
double Sphere::area() const { 
	return 4 * 3,14 * radius * radius;
}
double Sphere::volume() const { return (4.0 / 3.0) * 3,14 * radius * radius * radius; }
void Sphere::print(ostream& os) const {
	os << "Фигура: Sphere\n";
	os << "Радиус: " << radius << "\n";
}