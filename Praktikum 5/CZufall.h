#pragma once
#include <vector>
using namespace std;

class CZufall {
	public:
		int wert (int a, int b);
		void initialisiere (int n);
		vector<int> test (int a, int b, int N);
		vector<int> test_falsch (int a, int b, int N);
};