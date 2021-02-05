#include "symmetric_matrix.h"

symmetric_matrix::symmetric_matrix(vector<vector<double>> _matr) : matrix(_matr) {
	vector<int> _cols;
	int _rows1 = 0;
	for (auto i : _matr) {
		_cols.push_back(i.size());
		_rows1++;
	}
	int _cols1 = _matr.at(0).size();
	int _rows2 = count(_cols.begin(), _cols.end(), _cols.at(0));
	if (_rows1 != _rows2 || _rows1 != _cols1) {
		throw sm_error();
	}
	for (int i = 0; i < _cols1; i++) {
		for (int j = 0; j < _cols1; j++) {
			if (matr.at(i).at(j) != matr.at(j).at(i)) {
				throw sm_error();
			}
		}
	}
	rows = _rows1;
	cols = _cols1;
}

symmetric_matrix::symmetric_matrix(symmetric_matrix& T) : matrix(T) {}