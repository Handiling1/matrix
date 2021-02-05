#include "identity_matrix.h"

identity_matrix::identity_matrix(int _cols) : matrix(_cols, _cols) {
	for (int i = 0; i < _cols; i++) {
		matr.at(i).at(i) = 1;
	}
}

identity_matrix::identity_matrix(identity_matrix& T) : matrix(T) {}
