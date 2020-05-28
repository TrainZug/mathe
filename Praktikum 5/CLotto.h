#pragma once
#include <vector>
#include "CZufall.h"
using namespace std;

class CLotto {
	private:
		vector<int> tippzettel;
		vector<int> ziehung ();
		CZufall zufall;
		int richtige (vector<int>, vector<int>);
	public:
		CLotto (int);
		void set_tippzettel (vector<int>);
		int eine_ziehung ();
		int zwei_ziehungen ();
};
