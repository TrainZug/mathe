#pragma once
#include "CMyMatrix.h"

CMyMatrix::CMyMatrix(int r, int c)
{
	rows = r;
	cols = c;
	components.resize(cols);
	for (int i = 0; i < cols; i++) {
		CMyVektor vektor(rows);
		components.at(i) = vektor;
	}


}

int CMyMatrix::get_rows() const
{
	return rows;
}

int CMyMatrix::get_cols() const
{
	return cols;
}

void CMyMatrix::fill()
{
	for (int i = 0, c = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++, c++) {
			components.at(j)[i] = c;
		}
	}
}

const double CMyMatrix::det() const
{
	if (rows != 2 || cols != 2) {
		throw std::exception("nur 2x2 Matrix");
	}
	const double a = components.at(0)[0];
	const double b = components.at(0)[1];
	const double c = components.at(1)[0];
	const double d = components.at(1)[1];
	return a * d - b * c;
}

CMyVektor CMyMatrix::operator[](int col) const
{
	return components.at(col);
}

CMyVektor& CMyMatrix::operator[](int col)
{
	return components.at(col);
}

double CMyMatrix::operator()(int col, int row) const
{
	return components.at(col)[row];
}

double& CMyMatrix::operator()(int col, int row)
{
	return components.at(col)[row];
}

CMyMatrix CMyMatrix::inverse()
{
	if (rows != 2 || cols != 2 || det() == 0) {
		throw std::exception("nur 2x2 Matrix und det(A) != 0");
	}

	CMyMatrix inverse(rows, cols);

	const double a = components.at(0)[0];
	const double b = components.at(0)[1];
	const double c = components.at(1)[0];
	const double d = components.at(1)[1];

	const double e = 1 / (a * d - b * c);

	inverse(0, 0) = e * d;
	inverse(0, 1) = e * -b;
	inverse(1, 0) = e * -c;
	inverse(1, 1) = e * a;

	return inverse;
}


CMyVektor operator*(CMyMatrix A, CMyVektor x)
{
	CMyVektor ergebnis(A.get_rows());

	for (int i = 0; i < A.get_rows(); i++) {
		for (int j = 0; j < A.get_cols(); j++) {
			ergebnis[i] += A[j][i] * x[j];
		}
	}

	return ergebnis;
}

CMyMatrix operator*(CMyMatrix A, double x)
{
	CMyMatrix ergebnis = A;
	for (int i = 0; i < A.get_rows(); i++) {
		for (int j = 0; j < A.get_cols(); j++) {
			ergebnis[i][j] = ergebnis[i][j] * x;
		}
	}

	return ergebnis;
}

std::ostream& operator<<(std::ostream& os, const CMyMatrix& matrix)
{
	os << "( ";
	for (int i = 0; i < matrix.get_rows(); i++) {

		for (int j = 0; j < matrix.get_cols(); j++) {
			os << matrix[j][i];
			if (j < matrix.get_cols() - 1) {
				os << "; ";
			}
		}
		if (i < matrix.get_rows() - 1) {
			os << std::endl;
		}
	}
	os << " )";
	return os;
}
