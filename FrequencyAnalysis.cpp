#include "CryptoMath.h"
#include <iostream>
using namespace std;

int FrequencyMain() {
	string text;

	vector<double> result;
	cout << "Frequency Analysis\n\n";
	cout << "Enter text: ";
	cin >> text;

	result = freq(text);
	
	for (int i = 0; i < 26; i++) {
		cout << char('A' + i) << ": " << result[i] << '\n';
	}
	return 0;
}