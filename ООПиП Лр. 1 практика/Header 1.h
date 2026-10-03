#pragma once

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
	~TwoDimensionalArray() {
		freeMemory();
	}
	bool setSize(int r, int c);
	void allocMemory();
	void input();
	void output();
	void saveToFile(ofstream& fout) const; 
	int min() const;
	int max() const; 
	int getRows() const; 
	int getCols() const;
};
int menu();