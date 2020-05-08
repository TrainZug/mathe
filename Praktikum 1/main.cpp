#include "CMyVektor.h"
#include <iostream>

using namespace std;

double etest_funktion1d(CMyVektor);
double f(CMyVektor);
double g(CMyVektor);
double etest_funktion5a(CMyVektor);
double etest_funktion5b(CMyVektor);


CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x));
void max(CMyVektor x, double(*funktion)(CMyVektor x), double = 1.0);
void min(CMyVektor x, double(*funktion)(CMyVektor x), double = 1.0);


int main() {

	// Aufgabe 1
	double data1[]{ 1,2,3 };
	CMyVektor a(3, data1);
	cout << "a = " << a << endl;

	double data2[] = { 1,2,3 };
	CMyVektor b(3, data2);
	cout << "b = " << b << endl;

	try {
		CMyVektor c = a + b;
		cout << "c = a + b = " << c << endl;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}


	CMyVektor d = 2.0 * a;
	cout << "d = 2.0 * a = " << d << endl;


	CMyVektor e = -2 * a;
	cout << "e = -2.0 * a = " << e << endl;


	cout << endl << endl << endl;
	// Aufgabe 2
	double data3[] = { 1,2 };
	CMyVektor x1(2, data3);
	cout << "grad f(1,2) = " << gradient(x1, etest_funktion1d) << endl << endl << endl;


	// Aufgabe 3
	double data4[] = { 0.2, -2.1 };
	CMyVektor x2(2, data4);
	max(x2, f);

	cout << endl << endl << endl << "----------------------" << endl << endl << endl << endl;

	double data5[] = { 0, 0, 0 };
	CMyVektor x3(3, data5);
	max(x3, g, 0.1);


	return 0;
}

void max(CMyVektor x, double(*f)(CMyVektor x), double lambda)
{
	int schritte = 0;
	do {
		cout << "Schritt " << schritte++ << ": " << endl;
		cout << "x = " << x << endl;
		cout << "lambda = " << lambda << endl;
		cout << "f(x) = " << f(x) << endl;
		cout << "grad f(x) = " << gradient(x, f) << endl;
		cout << "||grad f(x)|| = " << gradient(x, f).get_length() << endl << endl;

		CMyVektor x_neu = x + lambda * gradient(x, f);

		cout << "x_neu = " << x_neu << endl;
		cout << "f(x_neu) = " << f(x_neu) << endl << endl;

		if (f(x_neu) > f(x)) {
			cout << "Test mit doppelter Schrittweite (lambda = " << lambda * 2 << "):" << endl;
			CMyVektor x_test = x + 2 * lambda * gradient(x, f);
			cout << "x_test = " << x_test << endl;
			cout << "f(x_test) = " << f(x_test) << endl;
			if (f(x_test) > f(x_neu)) {
				x = x_test;
				lambda *= 2;
				cout << "verdoppele Schrittweite!" << endl << endl;
			}
			else {
				x = x_neu;
				cout << "behalte alte Schrittweite!" << endl << endl;
			}
		}
		else if (f(x_neu) <= f(x)) {
			do {
				lambda /= 2;
				cout << "halbiere Schrittweite (lambda = " << lambda << "):" << endl;
				x_neu = x + lambda * gradient(x, f);
				cout << "x_neu = " << x_neu << endl;
				cout << "f(x_neu) = " << f(x_neu) << endl << endl;
			} while (f(x_neu) <= f(x));

			x = x_neu;

		}

		if (gradient(x, f).get_length() < pow(10, -5)) {
			cout << "Ende wegen ||grad f(x)||< 1e-5 bei" << endl;
			cout << "x = " << x << endl;
			cout << "lambda = " << lambda << endl;
			cout << "f(x) = " << f(x) << endl;
			cout << "grad f(x) = " << gradient(x, f) << endl;
			cout << "||grad f(x)|| = " << gradient(x, f).get_length() << endl << endl;
			return;
		}
		else if (schritte >= 25) {
			cout << "Ende wegen Schrittanzahl = 25 bei" << endl;
			cout << "x = " << x << endl;
			cout << "lambda = " << lambda << endl;
			cout << "f(x) = " << f(x) << endl;
			cout << "grad f(x) = " << gradient(x, f) << endl;
			cout << "||grad f(x)|| = " << gradient(x, f).get_length() << endl << endl;
			return;
		}

	} while (true);
}

void min(CMyVektor x, double(*f)(CMyVektor x), double lambda)
{
	int schritte = 0;
	do {
		cout << "Schritt " << schritte++ << ": " << endl;
		cout << "x = " << x << endl;
		cout << "lambda = " << lambda << endl;
		cout << "f(x) = " << f(x) << endl;
		cout << "grad f(x) = " << gradient(x, f) << endl;
		cout << "||grad f(x)|| = " << gradient(x, f).get_length() << endl << endl;

		CMyVektor x_neu = x - lambda * gradient(x, f);

		cout << "x_neu = " << x_neu << endl;
		cout << "f(x_neu) = " << f(x_neu) << endl << endl;

		if (f(x_neu) > f(x)) {
			cout << "Test mit doppelter Schrittweite (lambda = " << lambda * 2 << "):" << endl;
			CMyVektor x_test = x - lambda * gradient(x, f);
			cout << "x_test = " << x_test << endl;
			cout << "f(x_test) = " << f(x_test) << endl;
			if (f(x_test) > f(x_neu)) {
				x = x_test;
				lambda *= 2;
				cout << "verdoppele Schrittweite!" << endl << endl;
			}
			else {
				x = x_neu;
				cout << "behalte alte Schrittweite!" << endl << endl;
			}
		}
		else if (f(x_neu) <= f(x)) {
			do {
				lambda /= 2;
				cout << "halbiere Schrittweite (lambda = " << lambda << "):" << endl;
				x_neu = x - lambda * gradient(x, f);
				cout << "x_neu = " << x_neu << endl;
				cout << "f(x_neu) = " << f(x_neu) << endl << endl;
			} while (f(x_neu) <= f(x));

			x = x_neu;

		}

		if (gradient(x, f).get_length() < pow(10, -5)) {
			cout << "Ende wegen ||grad f(x)||< 1e-5 bei" << endl;
			cout << "x = " << x << endl;
			cout << "lambda = " << lambda << endl;
			cout << "f(x) = " << f(x) << endl;
			cout << "grad f(x) = " << gradient(x, f) << endl;
			cout << "||grad f(x)|| = " << gradient(x, f).get_length() << endl << endl;
			return;
		}
		else if (schritte >= 2) {
			cout << "Ende wegen Schrittanzahl = 25 bei" << endl;
			cout << "x = " << x << endl;
			cout << "lambda = " << lambda << endl;
			cout << "f(x) = " << f(x) << endl;
			cout << "grad f(x) = " << gradient(x, f) << endl;
			cout << "||grad f(x)|| = " << gradient(x, f).get_length() << endl << endl;
			return;
		}

	} while (true);
}

CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x))
{
	CMyVektor gradient(x.get_dimension());


	const double h = pow(10, -8);
	const double original = funktion(x);

	for (int i = 0; i < x.get_dimension(); i++) {

		// gewackelten Vektor aus x erstellen und zu i. Komponente h addieren
		CMyVektor gewackelt(x.get_dimension());
		for (int j = 0; j < x.get_dimension(); j++) {
			gewackelt[j] = x[j];
		}
		gewackelt[i] += h;


		gradient[i] = (funktion(gewackelt) - original) / h;
	}
	return gradient;
}


double etest_funktion1d(CMyVektor v) {
	double x = v[0];
	double y = v[1];
	return 2 * pow(x, 2) * pow(y, 2) + 2 * x * pow(y, 4); // 2x^2 * y^2 + 2xy^4
}


double f(CMyVektor v) {
	double x = v[0];
	double y = v[1];
	return sin(x * y) + sin(x) + cos(y); // sin(xy) + sin(x) + sin(y)
}

double g(CMyVektor v) {
	double x = v[0];
	double y = v[1];
	double z = v[2];
	return -(2 * pow(x, 2) - 2 * x * y + pow(y, 2) + pow(z, 2) - 2 * x - 4 * z); // -(2x^2 - 2xy + y^2 + z^2 - 2x - 4z)-
}


double etest_funktion5a(CMyVektor v) {
	double x = v[0];
	double y = v[1];
	return 3 * x * sin(2 * pow(x, 2) * y); // 3xsin(2x^2y);
}


double etest_funktion5b(CMyVektor v) {
	double x = v[0];
	double y = v[1];
	return 2 * pow(x, 3) + 6 * pow(y, 2) - 2 * x * y + 9; // 2x^3 + 6y^2 -2xy + 9
}