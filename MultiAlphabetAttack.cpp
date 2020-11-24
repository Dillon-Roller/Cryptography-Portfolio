#include "CryptoMath.h"
#include <iostream>
#include <vector>
using namespace std;

int MultiAlphabetAttackMain() {
	string cipher;
	string plaintext;
	string key;

	int choice;

	int length;
	cout << "Attack on Multi-Alphabet Ciphers\n\n";
	cout << "1. Find key length given ciphertext\n";
	cout << "2. Find key given key length and ciphertext\n";
	cin >> choice;

	if (choice == 1) {
		cout << "Enter plaintext: ";
		cin >> plaintext;
		cout << "Enter key: ";
		cin >> key;

		cipher = vigenereEncrypt(plaintext, key);
		
		length = vigenereAttackKeyLength(cipher);
		cout << "Most likely length of key: " << length << endl;
		length == (int)key.size() ? cout << "Lengths equal" : cout << "Lengths don't equal";
	}
	else if (choice == 2) {
		cout << "Enter plaintext: ";
		cin >> plaintext;
		cout << "Enter key: ";
		cin >> key;

		cipher = vigenereEncrypt(plaintext, key);
		cout << "\nCiphertext: " << cipher << "\n\n";
		length = (int)key.size();

		cout << "Attacking..\n";
		string text = vigenereAttackKey(cipher, length);
		
		cout << "Computed key: " << text << endl;
	}

	return 0;
}