#pragma once

#include "matrix.h"

class utm_error {
  string message = "Matrix is not upper triangular";
public:
  void ger_error() { cout << message << endl; }
};

class upper_triangular_matrix : public matrix {
public:
	upper_triangular_matrix(vector<vector<double>> _matr);
	upper_triangular_matrix(const upper_triangular_matrix& T);
};
