#pragma once

#include<cmath>
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

//Errors
class data_error {
  string message = "Can not create matrix from this data";
public:
  void ger_error() { cout << message << endl; }
};

class size_error {
  string message = "Sizes of matrix are incompatible";
public:
  void get_error() { cout << message << endl; }
};

class det_error {
  string message = "Matrix is not square";
public:
  void get_error() { cout << message << endl; }
};

class scalar_mul_error {
  string message = "Can not calculate scalar multiplication";
public:
  void get_error() { cout << message << endl; }
};

class trace_error {
  string message = "Matrix is not square";
public:
  void get_error() { cout << message << endl; }
};

class max_norm_error {
  string message = "Can not calculate max norm";
public:
  void get_error() { cout << message << endl; }
};

class angle_error {
  string message = "Can not calculate the angle";
public:
  void get_error() { cout << message << endl; }
};

class inverse_matrix_error {
  string message = "Can not calculate inverse matrix";
public:
  void get_error() { cout << message << endl; }
};

class file_error {
  string message = "File access error";
public:
  void get_error() { cout << message << endl; }
};

class matrix {
protected:
	int rows;
	int cols;
	vector<vector<double>> matr;
public:
	//Функции для 1
	matrix(int _rows = 1, int _cols = 1);
	matrix(vector<vector<double>> _matr);
	matrix(const matrix& T);
	~matrix() = default;
	friend matrix sum(const matrix& lhv, const matrix& rhv);
	friend matrix sub(const matrix& lhv, const matrix& rhv);
	friend matrix mul(const matrix& lhv, const matrix& rhv);
	friend matrix mul(const double& lhv, const matrix& rhv);
	friend matrix mul(const matrix& lhv, const double& rhv);
	friend matrix hadamard_product(const matrix& lhv, const matrix& rhv);
	matrix operator+(const matrix& rhv);
	matrix operator-(const matrix& rhv);
	matrix operator*(const matrix& rhv);
	friend matrix operator*(const double& lhv, const matrix& rhv);
	matrix operator*(const double& lhv);
	//Функции для 2
	friend double det(const matrix& T);
	friend double scalar_mul(const matrix& lhv, const matrix& rhv);
	friend double trace(const matrix& T);
	friend double norm(const matrix& T);
	friend double matrix_norm(const matrix& T);
	friend double max_norm(const matrix& T);
	friend matrix gauss_method(const matrix& T);
	//Функции для 3
	friend int matrix_rank(const matrix& T);
	friend matrix transpose(const matrix& T);
	friend double angle(const matrix& lhv, const matrix& rhv);
	friend matrix inverse_matrix(const matrix& T);
	//Функции для 4
  friend unsigned int size(const matrix& T);
	friend ostream& operator<<(ostream& out, const matrix& T);
	friend istream& operator>>(istream& is, matrix& T);
	void write(const string& path);
	void read(const string& path);
};
