#include<iostream>
#include <cmath>
#include "CMyvektor.h"
#include "C_DGLSolver.h"

using namespace std;

CMyVektor dlg_system (const CMyVektor, const double);
double dlg_dritter (const CMyVektor, const double);

int main () {
	{
		const CMyVektor y_start({0, 1});
		C_DGLSolver test(dlg_system);
		test.euler(0, 2, 100, y_start);
		test.heun(0, 2, 100, y_start);
	}
	cout << endl << endl;
	{
		const CMyVektor y_start({1, -1, 2});
		C_DGLSolver test(dlg_dritter);
		for (int i = 10; i <= 10000; i *= 10) {
			cout << "Abweichung bei Euler mit " << i << " Schritten: " << test.euler(1, 2, i, y_start, false) << endl;
			cout << "Abweichung bei Heun  mit " << i << " Schritten: " << test.heun(1, 2, i, y_start, false) << endl <<
				endl;
		}
	}

	return 0;
}

CMyVektor dlg_system (const CMyVektor y, const double x) {
	return CMyVektor({
		2 * y[1] - x * y[0],
		y[0] * y[1] - 2 * pow(x, 3)
	});
}

double dlg_dritter (CMyVektor y, double x) {
	const double y0 = y[0];
	const double y1 = y[1];
	const double y2 = y[2];
	return 2 * x * y1 * y2 + 2 * pow(y0, 2) * y1;
}
