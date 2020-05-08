#include "CMyMatrix.h"
#include <iostream>
#include <cmath>

using namespace std;

CMyVektor gradient (CMyVektor x, double (*funktion) (CMyVektor x));
CMyMatrix jacobi (CMyVektor x, CMyVektor (*funktion) (CMyVektor x));
CMyVektor aufgabe2 (CMyVektor x);
CMyVektor aufgabe3 (CMyVektor x);
CMyVektor etest3 (CMyVektor vek);
CMyVektor etest4 (CMyVektor vek);
void newton (CMyVektor x, CMyVektor (*f) (CMyVektor x));

int main () {
	// Aufgabe 1
	CMyMatrix matrix1(2, 2);
	matrix1.fill();

	CMyVektor x({1, 2});

	cout << matrix1 << endl << endl;
	try { cout << matrix1.inverse() << endl; }
	catch (std::exception e) {
		cout << e.what() << endl;
		//return 1;
	}

	cout << endl;

	CMyVektor mal = matrix1 * x;
	cout << mal << endl << endl << endl;

	// Aufgabe 2
	x = CMyVektor({1, 2, 0, 3});
	cout << "Jacobi:" << endl;
	cout << jacobi(x, aufgabe2) << endl << endl << endl << endl;

	// Aufgabe 3
	x = CMyVektor({1, 1});
	newton(x, aufgabe3);

	return 0;
}

CMyMatrix jacobi (CMyVektor x, CMyVektor (*funktion) (CMyVektor x)) {
	const double h = pow(10, -4);

	CMyVektor original  = funktion(x);
	CMyVektor gewackelt = x;
	CMyMatrix ergebnis(original.get_dimension(), x.get_dimension());

	for (int i = 0; i < x.get_dimension(); i++) {
		gewackelt[i] += h;
		if (i > 0) { gewackelt[i - 1] -= h; }

		CMyVektor f_gewackelt = funktion(gewackelt);
		for (int j = 0; j < original.get_dimension(); j++) { ergebnis[i][j] = (f_gewackelt[j] - original[j]) / h; }
	}

	return ergebnis;
}

void newton (CMyVektor x, CMyVektor (*f) (CMyVektor x)) {
	int schritte = 0;
	do {
		cout << "Schritt " << schritte++ << ": " << endl;
		cout << "x = " << x << endl;
		cout << "f(x) = " << f(x) << endl;
		cout << "f'(x) = " << jacobi(x, f) << endl;
		cout << "(f'(x))^(-1) = " << jacobi(x, f).inverse() << endl;

		CMyVektor dx = jacobi(x, f).inverse() * -1 * f(x);

		cout << "dx = " << dx << endl;
		cout << "||f(x)|| = " << f(x).get_length() << endl << endl;

		x = x + dx;

		if (f(x).get_length() < pow(10, -5)) {
			cout << "Ende wegen ||grad f(x)||< 1e-5 bei" << endl;
			cout << "x = " << x << endl;
			cout << "f(x) = " << f(x) << endl;
			cout << "||f(x)|| = " << f(x).get_length() << endl << endl;
			return;
		}
		else if (schritte >= 50) {
			cout << "Ende wegen Schrittanzahl = 50 bei" << endl;
			cout << "x = " << x << endl;
			cout << "f(x) = " << f(x) << endl;
			cout << "||f(x)|| = " << f(x).get_length() << endl << endl;
			return;
		}
	}
	while (true);
}

CMyVektor etest3 (CMyVektor vek) {
	const double x = vek[0];
	const double y = vek[1];
	const double z = vek[2];
	return CMyVektor({
		5 * pow(x, 2) * y,
		4 * pow(z, 2) + 3
	});
}

CMyVektor etest4 (CMyVektor vek) {
	const double x = vek[0];
	const double y = vek[1];
	return CMyVektor({
		6 * pow(x, 2) * y - 4 * x,
		5 * y
	});
}

CMyVektor aufgabe2 (CMyVektor x) {
	const double x1 = x[0];
	const double x2 = x[1];
	const double x3 = x[2];
	const double x4 = x[3];
	return CMyVektor({
		x1 * x2 * exp(x3),
		x2 * x3 * x4,
		x4
	});
}

CMyVektor aufgabe3 (CMyVektor vek) {
	const double x = vek[0];
	const double y = vek[1];
	return CMyVektor({
		pow(x, 3) * pow(y, 3) - 2 * y,
		x - 2
	});
}
