//Создать классы Circle, Square, Triangle, Shape, Oval, Sphere с
//необходимым набором полей и методов. Создать методы нахождения
//площади и объема фигур. Создать массив объектов базового класса и
//заполнить этот массив объектами базового и производных классов. Написать
//программу, которая создает объекты каждого из этих классов, и находит
//фигуру максимальную по площади и по объему, выводит данные о фигурах
//на экран и в файл. Классы должны содержать методы получения и изменения
//значений всех полей. Все поля классов должны быть объявлены с атрибутами
//private или protected.

#pragma once
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

class Shape {
protected: 
	char name[20];
	int type;
public:
	Shape(const char* n = "Shape", int t = 0) {
		strncpy_s(name, n, 19);
		name[19] = '\0';
		type = t;
	}
	const char* getName() const {
		return name;
	}
	int getType() const {
		return type;
	}
	void setName(const char* n) {
		strncpy_s(name, n, 19);
		name[19] = '\0';
	}
	void setType(int t) {
		type = t;
	}
};

class Circle : public Shape {
private: 
	double radius;
public:
	Circle(double r = 1.0);
	double getRadius() const;
	void setRadius(double r);
	double area() const;
	double volume() const;
	void print(ostream& os) const;
};

class Square : public Shape {
private:
	double side;
public:
	Square(double s = 1.0);

	double getSide() const;
	void setSide(double s);
	double area() const;
	double volume() const;
	void print(ostream& os) const;
};

class Triangle : public Shape {
private:
	double base, height;
public:
	Triangle(double b = 1.0, double h = 1.0);
	double getBase() const;
	double getHeight() const;
	void setBase(double b);
	void setHeight(double h);
	
	double area() const;
	double volume() const;
	void print(ostream& os) const;
};

class Oval : public Shape {
private:
	double a, b;
public:
	Oval(double a = 1.0, double b = 1.0);
	double getA() const;
	double getB() const;
	void setA(double x);
	void setB(double y);

	double area() const;   
	double volume() const; 
	void print(ostream& os) const;
};

class Sphere : public Shape {
private: 
	double radius;
public:
	Sphere(double r = 1.0);
	double getRadius() const;
	void setRadius(double r);
	double area() const;
	double volume() const;
	void print(ostream& os) const;
};