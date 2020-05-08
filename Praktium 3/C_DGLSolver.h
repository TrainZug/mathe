#pragma once
#include "CMyvektor.h"

class C_DGLSolver {
	private:
		double (*f_DGL_nterOrdnung) (CMyVektor y, double x);
		CMyVektor (*f_DGL_System) (CMyVektor y, double x);
		bool system;
		CMyVektor ableitungen (const CMyVektor y, const double x);
	public:
		C_DGLSolver (CMyVektor (*f_DGL_System) (CMyVektor y, double x));
		C_DGLSolver (double (*f_DGL_nterOrdnung) (CMyVektor y, double x));

		double euler (double x_start, double x_end, int schritte, CMyVektor y_Start, bool ausgabe=true);
		double heun (double x_start, double x_end, int schritte, CMyVektor y_Start, bool ausgabe=true);
};
