#include "CryptoMath.h"
#include <iostream>
#include <vector>
using namespace std;



int MultiAlphabetMain() {
	string text;
	string key;
	int decode;
	string result;
	
	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	cout << "Vigenère Cipher\n\n";
	cout << "Enter 0 (Encode) or 1 (Decode): ";
	cin >> decode;

	cout << "\nEnter text: ";
	cin >> text;

	cout << "Enter key: ";
	cin >> key;
	
	if (decode) {
		cout << "Decoding..\n";
		result = vigenereDecrypt(text, key);
		cout << "Plaintext: " << result;
	}
	else {
		cout << "\nEncoding..\n";
		result = vigenereEncrypt(text, key);
		cout << "Ciphertext: " << result;

		cout << "\n\nDecoding..\n";
		result = vigenereDecrypt(result, key);
		cout << "Plaintext: " << result << '\n\n';

		result == upper(text) ? cout << "Plaintexts match" : 
			cout << "Plaintexts don't match";
	}


	return 0;
}

