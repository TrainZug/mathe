#pragma once
#include <vector>
#include <iostream>
class CMyVektor {
private:
	int dimension;
	std::vector<double> components;
public:
	CMyVektor(int);
	CMyVektor(int, double[]);

	int get_dimension() const;
	void set_component(int, double);
	double get_component(int) const;
	double get_length() const;

	double operator[](int) const;
	double& operator[](int);
	CMyVektor operator+(CMyVektor b);
	CMyVektor operator-(CMyVektor b);


	friend CMyVektor operator*(double, const CMyVektor&);
	friend std::ostream& operator<<(std::ostream&, const CMyVektor&);
};

