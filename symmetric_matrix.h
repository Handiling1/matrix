#pragma once

#include "matrix.h"

class sm_error {
  string message = "Matrix is not symmetric";
public:
  void ger_error() { cout << message << endl; }
};

class symmetric_matrix : public matrix {
public:
	symmetric_matrix(vector<vector<double>> _matr);
	symmetric_matrix(symmetric_matrix& T);
};
