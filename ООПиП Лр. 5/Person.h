/*Создать классы «Учащийся колледжа», «Школьник», «Студент» с
необходимым набором полей и методов. Все классы должны содержать
методы получения и изменения всех полей. Программа должна выдавать
сведения об учащихся, имеющих количество пропусков больше указанного
пользователем. Использовать конструктор с параметрами, конструктор без
параметров, конструктор копирования. В класс добавить необходимый набор
полей и методов (минимум два поля и два метода) на свое усмотрение.
Предусмотреть метод для записи полученных данных в файл.*/
#pragma once
#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

class Person {
protected:
	char fio[50];
	int age;
	int absences;
public: 
	Person();
	Person(const char* f, int a, int b);
	Person(const Person& other);
	virtual ~Person() {};

	const char* getFio() const;
	int getAge() const;
	int getAbsences() const;

	void setFio(const char* f);
	void setAge(int a);
	void setAbsences(int a);

	virtual const char* getStatus() const = 0;
	virtual bool manyAbsences(int limit) const;
	virtual void saveToFile(ofstream& out) const = 0;
	virtual void print() const = 0;
};

class Schoolboy : public Person {
	int grade;
	int school;
public:
	Schoolboy();
	Schoolboy(const char* f, int a, int b, int g, int n);
	Schoolboy(const Schoolboy& s);

	const char* getStatus() const override;
	void print() const override;
	void saveToFile(ofstream& out) const override;
};

class CollegeStudent : public Person {
	char specialty[50];
	int course;

public:
	CollegeStudent();
	CollegeStudent(const char* f, int a, int ab, const char* sp, int c);
	CollegeStudent(const CollegeStudent& s);

	const char* getStatus() const override;
	void print() const override;
	void saveToFile(ofstream& out) const override;
};

class UniversityStudent : public Person {
	char faculty[50];
	int year;

public:
	UniversityStudent();
	UniversityStudent(const char* f, int a, int ab, const char* fac, int y);
	UniversityStudent(const UniversityStudent& s);

	const char* getStatus() const override;
	void print() const override;
	void saveToFile(ofstream& out) const override;
};

int inputInt(const char* msg);
double inputDouble(const char* msg);
void inputFio(char* buffer, int maxLen, const char* msg);