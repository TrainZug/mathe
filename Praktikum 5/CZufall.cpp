#include "CZufall.h"
#include <ctime>

int CZufall::wert (int a, int b) {
	return rand() % (b - a + 1) + a;
}

void CZufall::initialisiere (int n) {
	srand(n);
}

vector<int> CZufall::test (int a, int b, int N) {
	vector<int> ergebnis(b - a + 1, 0);
	for (int i = 0; i < N; i++) {
		ergebnis.at(wert(a, b) - a) += 1;
	}
	return ergebnis;
}

vector<int> CZufall::test_falsch (int a, int b, int N) {
	vector<int> ergebnis(b - a + 1, 0);
	for (int i = 0; i < N; i++) {
		initialisiere(time(nullptr));
		ergebnis.at(wert(a, b) - a) += 1;
	}
	return ergebnis;
}
