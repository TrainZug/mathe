#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "CKomplex.h"

using namespace std;

vector<CKomplex> werte_einlesen (string dateiname);
void werte_ausgeben (string dateiname, vector<CKomplex> werte, double epsilon = -1.0);
vector<CKomplex> ft (vector<CKomplex> werte, bool hin);
double max_differenz (vector<CKomplex>, vector<CKomplex>);

int main () {
	// originale daten
	vector<CKomplex> daten = werte_einlesen("Daten_original.txt");

	// erstes mal transformieren
	vector<CKomplex> hin = ft(daten, true);

	// ausgeben mit verschiedenen epsilon
	werte_ausgeben("Hin0.txt", hin);
	werte_ausgeben("Hin1.txt", hin, 0.1);
	werte_ausgeben("Hin2.txt", hin, 1.0);

	// einlesen
	vector<CKomplex> zurueck = werte_einlesen("Hin0.txt");

	// zurück transformieren
	zurueck = ft(zurueck, false);
	// maximale differenz zwischen werten ausgeben
	cout << "Maximale Abweichung bei epsilon = -1.0: " << max_differenz(daten, zurueck) << endl;

	zurueck = werte_einlesen("Hin1.txt");
	zurueck = ft(zurueck, false);
	cout << "Maximale Abweichung bei epsilon = 0.1:  " << max_differenz(daten, zurueck) << endl;

	zurueck = werte_einlesen("Hin2.txt");
	zurueck = ft(zurueck, false);
	cout << "Maximale Abweichung bei epsilon = 1.0:  " << max_differenz(daten, zurueck) << endl;

	return 0;
}

vector<CKomplex> ft (vector<CKomplex> werte, bool hin) {
	vector<CKomplex> ergebnis;
	int N        = werte.size();
	int richtung = hin ? 1 : -1;
	double sqrtN = 1.0 / sqrt(N);

	// über alle werte loopen
	for (int n = 0; n < N; n++) {
		CKomplex tmp_sum;
		// werte aufsummieren mit Formel:
		// hin: (2*pi*k*n) / N
		// zurück: -(2*pi*k*n) / N
		// und die Summe multiplizieren mit 1/sqrt(N)
		for (int k = 0; k < N; k++) {
			tmp_sum = tmp_sum + (werte[k] * CKomplex((richtung * (2 * 3.141592653589793238463 * k * n)) / N));
		}
		ergebnis.push_back(sqrtN * tmp_sum);
	}
	return ergebnis;
}

double max_differenz (vector<CKomplex> a, vector<CKomplex> b) {
	double max = abs((a[0] - b[0]).abs());

	for (int i = 1; i < a.size(); i++) {
		double differenz = abs((a[i] - b[i]).abs());

		if (differenz > max) {
			max = differenz;
		}
	}
	return max;
}

vector<CKomplex> werte_einlesen (const string dateiname) {
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	// File oeffnen
	ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i       = 0; i < N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof()) {
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben (const string dateiname, vector<CKomplex> werte, double epsilon) {
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
	// File schliessen
	fp.close();
}
