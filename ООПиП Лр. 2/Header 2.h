#pragma once
//14. Создать класс Array для работы с двумерными массивами (как
//целочисленными, так и дробными).Найти наибольший элемент массива,
//который кратен двум.Найти сумму номеров минимального и максимального
//элементов массива.Память под массив выделять динамически.Размер
//массива указывает пользователь.Необходимо обязательно освобождать
//память, выделенную под массив.Написать свой манипулятор, выводящий
//содержимое массива в табличном виде.

#include<iomanip>
#include<fstream>

using namespace std;

class Array {
private: 
	double** a;
	int rows;
	int cols;

public:
	Array();
	Array(int r, int c);
	Array(const Array& obj);
	~Array();

	bool setrows(int r);
	bool setcols(int c);
	bool setelements(int r, int c, double value);

	void input();
	void savetofile(ofstream& fout) const;
	double max() const;
	double sum() const;

	int getrows() {
		return rows;
	}
	int getcols() {
		return cols;
	}
	double get(int i, int j) const {
		return a[i][j];
	}
};

int menu();

//манипулятор
ostream& table(ostream& stream);
