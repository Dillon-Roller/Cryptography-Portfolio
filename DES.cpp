#include "CryptoMath.h"
#include <iostream>
#include <vector>
using namespace std;

int DESMain() {
	
	string msg;
	string L0, R0;
	string key;
	cout << "Simplified DES\n\n"; 
	cout << "Enter message (12 bits): ";
	cin >> msg;
	cout << "Enter key (8 bits): ";
	cin >> key;
	
	string result = DEShelper(msg, key, 4);

	cout << "\nCipherText: " << result << endl;

	return 0;
}