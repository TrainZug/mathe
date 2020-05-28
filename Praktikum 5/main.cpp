#include <ctime>
#include <iostream>
#include "CZufall.h"
#include <windows.h>

#include "CLotto.h"

using namespace std;

void print_vector (const vector<int> & vector);
double monte_carlo (int n);
double monte_carlo_zwei_ziehungen (int n);

int main () {

	// 1a) und b)
	for (int i = 1; i < 6; i++) {
		CZufall zufall;
		zufall.initialisiere(1);
		const vector<int> test = zufall.test(3, 7, 10000);
		cout << i << ". Durchlauf mit Seed=1: ";
		print_vector(test);
	}
	cout << endl;

	// 1c)
	for (int i = 1; i < 6; i++) {
		CZufall zufall;
		zufall.initialisiere(i);
		const vector<int> test = zufall.test(3, 7, 10000);
		cout << i << ". Durchlauf mit Seed=" << i << ": ";
		print_vector(test);
	}
	cout << endl;

	// 1d)
	for (int i = 1; i < 6; i++) {
		CZufall zufall;
		const int seed = time(nullptr);
		zufall.initialisiere(seed);
		const vector<int> test = zufall.test(3, 7, 10000);
		cout << i << ". Durchlauf mit Seed=" << seed << ": ";
		print_vector(test);
		Sleep(1000);
	}
	cout << endl;

	// 3)
	cout << "Tippzettel: ";
	print_vector({4, 8, 15, 16, 23, 42});
	cout << "Wahrscheinlichkeit das bei 100.000 Ziehungen drei gleiche kommen: " << monte_carlo(100000) << "%" << endl;
	cout << "Wahrscheinlichkeit das bei 1.000.000 Ziehungen drei gleiche kommen: " << monte_carlo(1000000) << "%" <<
		endl << endl;

	cout << "Wahrscheinlichkeit das bei 100.000 Durchlaeufen zwei Ziehungen drei gleiche Zahlen haben: " <<
		monte_carlo_zwei_ziehungen(100000) << "%" << endl;
	cout << "Wahrscheinlichkeit das bei 1.000.000 Durchlaeufen zwei Ziehungen drei gleiche Zahlen haben: " <<
		monte_carlo_zwei_ziehungen(1000000) << "%" << endl;

	return 0;
}

double monte_carlo (const int n) {
	CLotto lotto(-1);
	lotto.set_tippzettel({4, 8, 15, 16, 23, 42});

	int drei_richtige = 0;

	for (int i = 0; i < n; i++) {
		if (lotto.eine_ziehung() == 3) {
			drei_richtige++;
		}
	}
	return (double(drei_richtige) / double(n)) * 100;
}

double monte_carlo_zwei_ziehungen (int n) {
	CLotto lotto(-1);
	int drei_gleiche = 0;

	for (int i = 0; i < n; i++) {
		if (lotto.zwei_ziehungen() == 3) {
			drei_gleiche++;
		}
	}
	return (double(drei_gleiche) / double(n)) * 100;
}

void print_vector (const vector<int> & vector) {
	for (int i: vector) {
		cout << i << " ";
	}
	cout << endl;
}
