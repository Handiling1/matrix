#pragma once

#include "matrix.h"

class ltm_error {
  string message = "Matrix is not lower triangular";
public:
  void ger_error() { cout << message << endl; }
};

class lower_triangular_matrix : public matrix {
public:
	lower_triangular_matrix(vector<vector<double>> _matr);
	lower_triangular_matrix(const lower_triangular_matrix& T);
};
