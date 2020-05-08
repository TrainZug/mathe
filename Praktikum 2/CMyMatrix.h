#pragma once
#include "CMyVektor.h"
#include <vector>

class CMyMatrix
{
private:
	int rows, cols;
	std::vector<CMyVektor> components;
public:
	CMyMatrix(int, int);

	int get_rows() const;
	int get_cols() const;

	void fill();

	const double det() const;

	CMyMatrix inverse();

	CMyVektor operator[](int col) const;
	CMyVektor& operator[](int col);


	double operator()(int row, int col) const;
	double& operator()(int row, int col);

	friend CMyVektor operator*(CMyMatrix A, CMyVektor x);
	friend CMyMatrix operator*(CMyMatrix A, double lambda);
	friend std::ostream& operator<<(std::ostream&, const CMyMatrix&);
};

