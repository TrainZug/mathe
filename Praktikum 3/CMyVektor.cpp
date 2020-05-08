#include "CMyVektor.h"
#include <math.h>
#include <iostream>

CMyVektor::CMyVektor()
{
}

CMyVektor::CMyVektor(int dim)
{
	dimension = dim;
	components.resize(dim);
	for (int i = 0; i < dim; i++) {
		components.at(i) = 0;
	}
}

CMyVektor::CMyVektor(int dim, double data[])
{
	dimension = dim;
	components.resize(dim);
	for (int i = 0; i < dim; i++) {
		components.at(i) = data[i];
	}
}

CMyVektor::CMyVektor(std::vector<double> data)
{	
	dimension = data.size();;
	components.resize(dimension);
	for (int i = 0; i < dimension; i++) {
		components.at(i) = data.at(i);
	}
}
void CMyVektor::set_dimension(int d)
{
	dimension = d;
	components.resize(dimension);
}

int CMyVektor::get_dimension() const
{
	return dimension;
}

void CMyVektor::set_component(int i, double data)
{
	components.at(i) = data;
}

double CMyVektor::get_component(int i) const
{
	return components.at(i);
}

double CMyVektor::get_length() const
{
	double length = 0;
	for (int i = 0; i < dimension; i++) {
		length += components.at(i) * components.at(i);
	}
	length = sqrt(length);
	return length;
}

CMyVektor CMyVektor::operator+(CMyVektor b)
{
	if (dimension != b.dimension) {
		throw std::exception("Unterschiedliche Dimension! Addition geht nicht");
	}

	CMyVektor vektor(dimension);
	for (int i = 0; i < dimension; i++) {
		vektor[i] = get_component(i) + b[i];
	}
	return vektor;
}

CMyVektor CMyVektor::operator-(CMyVektor b)
{
	if (dimension != b.dimension) {
		throw std::exception("Unterschiedliche Dimension! Subtraktion geht nicht");
	}
	CMyVektor vektor(dimension);
	for (int i = 0; i < dimension; i++) {
		vektor[i] = get_component(i) - b[i];
	}
	return vektor;
}


double CMyVektor::operator[](int i) const
{
	return components.at(i);
}

double& CMyVektor::operator[](int i)
{
	return components.at(i);
}

CMyVektor operator*(double lambda, const CMyVektor& a)
{
	CMyVektor vektor(a.get_dimension());
	for (int i = 0; i < a.get_dimension(); i++) {
		vektor[i] = a[i] * lambda;
	}
	return vektor;
}

std::ostream& operator<<(std::ostream& os, const CMyVektor& vektor)
{
	const int dimension = vektor.get_dimension();
	os << "( ";
	for (int i = 0; i < dimension; i++) {
		os << vektor[i];
		if (i < dimension - 1) {
			std::cout << "; ";
		}
	}
	os << " )";
	return os;
}