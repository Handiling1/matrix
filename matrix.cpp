#include "matrix.h"

matrix::matrix(int _rows, int _cols) {
	if (_rows <= 0) {
		throw data_error();
	}
	if (_cols <= 0) {
		throw data_error();
	}
	rows = _rows;
	cols = _cols;
	matr.resize(rows);
	for (int i = 0; i < rows; i++) {
		matr[i].resize(cols);
	}
}

matrix::matrix(vector<vector<double>> _matr) : matr(_matr) {
	vector<int> _cols;
	int _rows1 = 0;
	for (auto i : _matr) {
		_cols.push_back(i.size());
		_rows1++;
	}
	int _cols1 = _matr.at(0).size();
	int _rows2 = count(_cols.begin(), _cols.end(), _cols.at(0));
	if (_rows1 != _rows2) {
		throw data_error();
	}
	rows = _rows1;
	cols = _cols1;
}

matrix::matrix(const matrix& T) : rows(T.rows), cols(T.cols), matr(T.matr) {}

matrix matrix::operator+(const matrix& rhv) {
	return sum(*this, rhv);
}

matrix matrix::operator-(const matrix& rhv) {
	return sub(*this, rhv);
}

matrix matrix::operator*(const matrix& rhv) {
	return mul(*this, rhv);
}

matrix operator*(const double& lhv, const matrix& rhv) {
	return mul(lhv, rhv);
}

matrix matrix::operator*(const double& rhv) {
	return mul(*this, rhv);
}

void matrix::write(const string& path) {
	ofstream out(path, ios::binary | ios::trunc);
	if (out.is_open()) {
    out.write((char*)&this->rows, sizeof(int));
    out.write((char*)&this->cols, sizeof(int));
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        out.write((char*)&this->matr.at(i).at(j), sizeof(double));
      }
    }
		out.close();
	}
	else {
		out.close();
		throw file_error();
	}
}

void matrix::read(const string& path) {
	ifstream in(path, ios::in | ios::binary);
	if (in.is_open()) {
    int _rows, _cols;
    double tmp;
    vector<vector<double>> _matr;
    in.read((char*)&_rows, sizeof(int));
    in.read((char*)&_cols, sizeof(int));
    _matr.resize(_rows);
    for (int i = 0; i < _rows; i++) {
      _matr.at(i).resize(_cols);
      for (int j = 0; j < _cols; j++) {
        in.read((char*)&tmp, sizeof(double));
        _matr.at(i).at(j) = tmp;
      }
    }
    matrix m(_matr);
		*this = m;
		in.close();
	}
	else {
		in.close();
		throw file_error();
	}
}

matrix transpose(const matrix& T) {
	vector<vector<double>> transposed(T.cols);
	for (int i = 0; i < T.cols; i++) {
		transposed.at(i).resize(T.rows);
		for (int j = 0; j < T.rows; j++) {
			transposed.at(i).at(j) = T.matr.at(j).at(i);
		}
	}
	matrix copy(transposed);
	return copy;
}

double angle(const matrix& lhv, const matrix& rhv) {
	if (norm(lhv) == 0 || norm(rhv) == 0) {
		throw angle_error();
	}
	double alpha = scalar_mul(lhv, rhv) / (norm(lhv) * norm(rhv));
	return acos(alpha) * 180 / (atan(1) * 4);
}

matrix inverse_matrix(const matrix& T) {
	if (T.rows != T.cols || det(T) == 0) {
		throw inverse_matrix_error();
	}
	vector<vector<double>> extended_vect(T.rows);
	for (int i = 0; i < T.rows; i++) {
		extended_vect.at(i).resize(2 * T.cols);
		extended_vect.at(i).at(T.rows + i) = 1;
		for (int j = 0; j < T.cols; j++) {
			extended_vect.at(i).at(j) = T.matr.at(i).at(j);
		}
	}
	matrix extended_matrix1(extended_vect);
	matrix extended_matrix2 = gauss_method(extended_matrix1);
	for (int i = 0; i < T.rows; i++) {
		double koeff = 1 / extended_matrix2.matr.at(i).at(i);
		if (koeff == 0) { continue; }
		for (int j = 0; j < extended_matrix2.cols; j++) {
			extended_matrix2.matr.at(i).at(j) *= koeff;
		}
	}
	vector<vector<double>> inverse_vect(T.rows);
	for (int i = 0; i < T.rows; i++) {
		inverse_vect.at(i).resize(T.cols);
		for (int j = 0; j < T.cols; j++) {
			inverse_vect.at(i).at(j) = extended_matrix2.matr.at(i).at(T.rows + j);
		}
	}
	return matrix(inverse_vect);
}

ostream& operator<<(ostream& out, const matrix& T) {
	for (int i = 0; i < T.rows; i++) {
		for (int j = 0; j < T.cols; j++) {
			out << left << setw(4) << T.matr.at(i).at(j) << "\t";
		}
		out << endl;
	}
	return out;
}

istream& operator>>(istream& in, matrix& T) {
	string buf;
	string lines;
	double tmp;
	int _rows = -1;
	while (!in.eof()) {
		getline(in, buf);
		lines.append(buf);
		_rows++;
	}
	stringstream ss(lines);
	vector<double> matr_in_line;
	while (ss >> tmp) {
		matr_in_line.push_back(tmp);
	}
	int _cols = matr_in_line.size() / _rows;
	vector<vector<double>> _matr(_rows);
	for (int i = 0; i < _rows; i++) {
		_matr.at(i).resize(_cols);
		for (int j = 0; j < _cols; j++) {
			_matr.at(i).at(j) = matr_in_line.at(i * _rows + j);
		}
	}
	matrix m(_matr);
	T = m;
	return in;
}

matrix sum(const matrix& lhv, const matrix& rhv) {
	if (lhv.cols != rhv.cols || lhv.rows != lhv.rows) {
		throw size_error();
	}
	matrix result(lhv.rows, lhv.cols);
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.matr.at(i).at(j) = lhv.matr.at(i).at(j) + rhv.matr.at(i).at(j);
		}
	}
	return result;
}

matrix sub(const matrix& lhv, const matrix& rhv) {
	if (lhv.cols != rhv.cols || lhv.rows != rhv.rows) {
		throw size_error();
	}
	matrix result(lhv.rows, lhv.cols);
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.matr.at(i).at(j) = lhv.matr.at(i).at(j) - rhv.matr.at(i).at(j);
		}
	}
	return result;
}

matrix mul(const matrix& lhv, const matrix& rhv) {
	if (lhv.cols != rhv.rows) {
		throw size_error();
	}
	matrix result(lhv.rows, rhv.cols);
	for (int i = 0; i < lhv.rows; i++) {
		for (int j = 0; j < rhv.cols; j++) {
			result.matr.at(i).at(j) = 0;
			for (int k = 0; k < lhv.cols; k++) {
				result.matr.at(i).at(j) += lhv.matr.at(i).at(k) * rhv.matr.at(k).at(j);
			}
		}
	}
	return result;
}

matrix mul(const double& lhv, const matrix& rhv) {
	matrix result(rhv.rows, rhv.cols);
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.matr.at(i).at(j) = lhv * rhv.matr.at(i).at(j);
		}
	}
	return result;
}

matrix mul(const matrix& lhv, const double& rhv) {
	matrix result(lhv.rows, lhv.cols);
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.matr.at(i).at(j) = lhv.matr.at(i).at(j) * rhv;
		}
	}
	return result;
}

matrix hadamard_product(const matrix& lhv, const matrix& rhv) {
	if (lhv.cols != rhv.cols || lhv.rows != rhv.rows) {
		throw size_error();
	}
	matrix result(lhv.rows, lhv.cols);
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			result.matr.at(i).at(j) = lhv.matr.at(i).at(j) * rhv.matr.at(i).at(j);
		}
	}
	return result;
}

double det(const matrix& T) {
	if (T.rows != T.cols) {
		throw det_error();
	}
	matrix copy = gauss_method(T);
	double det = 1;
	for (int i = 0; i < copy.rows; i++) {
		det *= copy.matr.at(i).at(i);
	}
	return det;
}

double scalar_mul(const matrix& lhv, const matrix& rhv) {
	double scalar_mul = 0;
	if (lhv.rows == 1 && rhv.rows == 1 && lhv.cols == lhv.cols) {
		for (int i = 0; i < lhv.cols; i++) {
			scalar_mul += lhv.matr.at(0).at(i) * rhv.matr.at(0).at(i);
		}
	}
	else if (lhv.cols == 1 && rhv.cols == 1 && lhv.rows == lhv.rows) {
		for (int i = 0; i < lhv.rows; i++) {
			scalar_mul += lhv.matr.at(i).at(0) * rhv.matr.at(i).at(0);
		}
	}
	else {
		throw scalar_mul_error();
	}
	return scalar_mul;
}

double trace(const matrix& T) {
	if (T.rows != T.cols) {
		throw trace_error();
	}
	double trace = 0;
	for (int i = 0; i < T.rows; i++) {
		trace += T.matr.at(i).at(i);
	}
	return trace;
}

double norm(const matrix& T) {
	return sqrt(scalar_mul(T, T));
}

double matrix_norm(const matrix& T) {
	double matrix_norm = 0;
	for (int i = 0; i < T.rows; i++) {
		for (int j = 0; j < T.cols; j++) {
			matrix_norm += fabs(T.matr.at(i).at(j) * T.matr.at(i).at(j));
		}
	}
	return sqrt(matrix_norm);
}

double max_norm(const matrix& T) {
	double max_norm = T.matr.at(0).at(0);
	if (T.rows == 1) {
		for (int i = 0; i < T.cols; i++) {
			if (max_norm < fabs(T.matr.at(0).at(i))) {
				max_norm = fabs(T.matr.at(0).at(i));
			}
		}
		return max_norm;
	}
	else if (T.cols == 1) {
		for (int i = 0; i < T.rows; i++) {
			if (max_norm < fabs(T.matr.at(i).at(0))) {
				max_norm = fabs(T.matr.at(i).at(0));
			}
		}
		return max_norm;
	}
	else {
		throw max_norm_error();
	}
}

matrix gauss_method(const matrix& T) {
	matrix copy = T;
	for (int i = 0; i < copy.rows; i++) {
		double d_elem = copy.matr.at(i).at(i);
		if (d_elem == 0) { continue; }
		for (int k = i + 1; k < copy.rows; k++) {
			double koeff = -copy.matr.at(k).at(i) / d_elem;
			for (int j = i; j < copy.cols; j++) {
				copy.matr.at(k).at(j) += copy.matr.at(i).at(j) * koeff;
			}
		}
	}
	for (int i = copy.rows - 1; i >= 0; i--) {
		double d_elem = copy.matr.at(i).at(i);
		if (d_elem == 0) { continue; }
		for (int k = i - 1; k >= 0; k--) {
			double koeff = -copy.matr.at(k).at(i) / d_elem;
			for (int j = 0; j < copy.cols; j++) {
				copy.matr.at(k).at(j) += copy.matr.at(i).at(j) * koeff;
			}
		}
	}
	return copy;
}

int matrix_rank(const matrix& T) {
  int rank = max(T.rows, T.cols);
	matrix copy = gauss_method(T);
	bool zero_row = false;
	for (int i = 0; i < copy.rows; i++) {
		for (int j = 0; j < copy.cols; j++) {
			if (copy.matr.at(i).at(j) == 0) {
				zero_row = true;
			}
			else {
				zero_row = false;
				break;
			}
		}
		if (zero_row == true) {
			--rank;
		}
	}
	return rank;
}

unsigned int size(const matrix& T) {
	return 2 * sizeof(int) + T.rows * T.cols * sizeof(double);
}