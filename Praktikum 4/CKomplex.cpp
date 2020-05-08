#include "CKomplex.h"
#include <cmath>
using namespace std;

CKomplex::CKomplex (double a, double b) : a{a}, b{b} {
}

CKomplex::CKomplex (double phi) {
	a = cos(phi);
	b = sin(phi);
}

double CKomplex::re () {
	return a;
}

double CKomplex::im () {
	return b;
}

double CKomplex::abs () {
	return sqrt(pow(a, 2) + pow(b, 2));
}

CKomplex operator+ (CKomplex c1, CKomplex c2) {
	const double a = c1.re() + c2.re();
	const double b = c1.im() + c2.im();
	return CKomplex(a, b);
}

CKomplex operator* (CKomplex c1, CKomplex c2) {
	const double a = c1.re() * c2.re();
	const double b = c1.im() * c2.im();
	return CKomplex(a, b);
}

CKomplex operator* (double d, CKomplex c2) {
	const double a = c2.re() * d;
	const double b = c2.im() * d;
	return CKomplex(a, b);
}
