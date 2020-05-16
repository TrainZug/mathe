#pragma once
class CKomplex {
	double a, b;
	public:
		CKomplex ();
		CKomplex (double a, double b);
		CKomplex (double phi);
		double re ();
		double im ();
		double abs ();
};

CKomplex operator+ (CKomplex c1, CKomplex c2);
CKomplex operator* (CKomplex c1, CKomplex c2);
CKomplex operator* (double d, CKomplex c2);
