#include "diagonal_matrix.h"

diagonal_matrix::diagonal_matrix(vector<double> elements) : matrix(elements.size(), elements.size()) {
	for (int i = 0; i < elements.size(); i++) {
		matr.at(i).at(i) = elements.at(i);
	}
}

diagonal_matrix::diagonal_matrix(const diagonal_matrix& T) : matrix(T) {}
