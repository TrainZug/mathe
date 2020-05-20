#include "CKomplex.h"
#include <cmath>
using namespace std;

CKomplex::CKomplex () {
	a = 0;
	b = 0;
}

CKomplex::CKomplex (double a1, double b1) {
	a = a1;
	b = b1;
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
	return CKomplex(c1.re() + c2.re(), c1.im() + c2.im());
}

CKomplex operator- (CKomplex c1, CKomplex c2) {
	return CKomplex(c1.re() - c2.re(), c1.im() - c2.im());
}

CKomplex operator* (CKomplex c1, CKomplex c2) {
	const double a = c1.re() * c2.re() + c1.im() * c2.im() * (-1);
	const double b = c1.re() * c2.im() + c1.im() * c2.re();
	return CKomplex(a, b);
}

CKomplex operator* (double d, CKomplex c2) {
	return CKomplex(d * c2.re(), d * c2.im());
}
