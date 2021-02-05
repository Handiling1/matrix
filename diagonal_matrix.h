#pragma once

#include "matrix.h"

class diagonal_matrix : public matrix {
public:
	diagonal_matrix(vector<double> elements);
	diagonal_matrix(const diagonal_matrix& T);
};
