#include "lower_triangular_matrix.h"

lower_triangular_matrix::lower_triangular_matrix(vector<vector<double>> _matr) : matrix(_matr) {
	vector<int> _cols;
	int _rows1 = 0;
	for (auto i : _matr) {
		_cols.push_back(i.size());
		_rows1++;
	}
	int _cols1 = _matr.at(0).size();
	int _rows2 = count(_cols.begin(), _cols.end(), _cols.at(0));
	if (_rows1 != _rows2 || _rows1 != _cols1) {
		throw ltm_error();
	}
	for (int i = 0; i < _cols1; i++) {
		for (int j = i + 1; j < _cols1; j++) {
			if (matr.at(i).at(j) != 0) {
				throw ltm_error();
			}
		}
	}
}

lower_triangular_matrix::lower_triangular_matrix(const lower_triangular_matrix& T) : matrix(T) {}
