#include <iostream>
#include "C_DGLSolver.h"
using namespace std;

C_DGLSolver::C_DGLSolver (CMyVektor (*f_DGL_System) (CMyVektor y, double x)) {
	system             = true;
	this->f_DGL_System = f_DGL_System;
}

C_DGLSolver::C_DGLSolver (double (*f_DGL_nterOrdnung) (CMyVektor y, double x)) {
	system                  = false;
	this->f_DGL_nterOrdnung = f_DGL_nterOrdnung;
}

CMyVektor C_DGLSolver::ableitungen (const CMyVektor y, const double x) {
	CMyVektor erg;
	if (system) {
		erg = f_DGL_System(y, x);
	} else {
		const int dim = y.get_dimension();
		erg.set_dimension(dim);

		for (int i = 0; i < dim - 1; i++) {
			erg[i] = y[i + 1];
		}
		erg[dim - 1] = f_DGL_nterOrdnung(y, x);
	}
	return erg;
}

double C_DGLSolver::euler (double x_start, double x_end, int schritte, CMyVektor y_Start, bool ausgabe) {
	const double h = (x_end - x_start) / schritte;

	CMyVektor y(y_Start.get_dimension());
	CMyVektor y_vorher = y_Start;

	for (int i = 0; i < schritte; i++) {
		CMyVektor y_abgeleitet = ableitungen(y_vorher, x_start);
		y                      = y_vorher + h * y_abgeleitet;

		if (ausgabe) {
			cout << "Schritt " << i << ":" << endl;
			cout << "\tx = " << x_start << endl;
			cout << "\ty = " << y_vorher << endl;
			cout << "\ty' = " << y_abgeleitet << endl << endl;
		}

		x_start += h;
		y_vorher = y;
	}
	if (ausgabe) {
		cout << "Ende bei" << endl;
		cout << "\tx = " << x_start << endl;
		cout << "\ty = " << y_vorher << endl;
	}
	return (y[0] - 0.5);
}

double C_DGLSolver::heun (double x_start, double x_end, int schritte, CMyVektor y_Start, bool ausgabe) {
	double h        = (x_end - x_start) / schritte;
	int d           = y_Start.get_dimension();
	double x_neu    = x_start, x_alt;
	CMyVektor y_neu = y_Start, y_hilf(d), y_mittel(d), next(d);

	for (int i = 0; i < schritte; i++) {
		y_hilf = y_neu;

		if (ausgabe) {
			cout << "Schritt " << i << ":" << endl;
			cout << "\tx = " << x_neu << endl;
			cout << "\ty = " << y_hilf << endl;
			cout << "\ty'_orig = " << ableitungen(y_hilf, x_neu) << endl << endl;
		}

		y_neu = y_neu + h * ableitungen(y_neu, x_neu);
		x_alt = x_neu;
		x_neu += h;
		next = ableitungen(y_neu, x_neu);
		y_mittel = 0.5 * (ableitungen(y_hilf, x_alt) + next); // Ymittel = 0.5* (f(x0,y(x0)) + f(x1,y1))

		if (ausgabe) {
			cout << "\ty_test = " << y_neu << endl;
			cout << "\ty'_test = " << next << endl << endl;
			cout << "\ty'_mittel = " << y_mittel << endl << endl;
		}

		y_neu = y_hilf + h * y_mittel; // schritt mit mittel
	}

	if (ausgabe) {
		cout << "Ende bei" << endl;
		cout << "\tx = " << x_neu << endl;
		cout << "\ty = " << y_neu << endl;
	}

	return (y_neu[0] - 0.5);
}
