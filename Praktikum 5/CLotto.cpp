#include "CLotto.h"
#include <ctime>

bool find (const vector<int> & vec, const int wert) {
	bool gefunden = false;
	for (int i: vec) {
		if (i == wert) {
			gefunden = true;
		}
	}
	return gefunden;
}

CLotto::CLotto (int n) {
	const int seed = (n < 0) ? time(nullptr) : n;
	zufall.initialisiere(seed);
}

void CLotto::set_tippzettel (vector<int> zettel) {
	tippzettel = zettel;
}

vector<int> CLotto::ziehung () {
	vector<int> gezogene;
	int anzahl_gezogene = 0;
	while (anzahl_gezogene < 6) {
		const int gezogen = zufall.wert(1, 49);
		if (!find(gezogene, gezogen)) {
			gezogene.push_back(gezogen);
			anzahl_gezogene++;
		}
	}
	return gezogene;
}

int CLotto::eine_ziehung () {
	vector<int> gezogene = ziehung();
	return richtige(gezogene, tippzettel);
}

int CLotto::zwei_ziehungen () {
	vector<int> gezogene1 = ziehung();
	vector<int> gezogene2 = ziehung();
	return richtige(gezogene1, gezogene2);
}

int CLotto::richtige (vector<int> a, vector<int> b) {
	int richtige = 0;
	for (int i: a) {
		for (int j: b) {
			if (i == j) {
				richtige++;
				break;
			}
		}
	}
	return richtige;
}
