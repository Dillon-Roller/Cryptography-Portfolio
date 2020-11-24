#include "CryptoMath.h"
#include <iostream>

int affineCipherMain()
{
	int a;
	int b;
	int choice;
	string text;

	cout << "Affine Cipher\n\n";

	cout << "Enter a: ";
	cin >> a;
	cout << "Enter b: ";
	cin >> b;

	cout << "\nEnter 0 (Encode) or 1 (Decode): ";
	cin >> choice;
	
	switch (choice) {
		case 0: {
			cout << "Enter plaintext: ";
			cin >> text;

			cout << "\nEncoding..\n";
			text = affineEncode(a, b, text);
			cout << "Ciphertext: " << text << "\n\n";

			cout << "Decoding..\n";
			text = affineDecode(a, b, text);
			cout << "Plaintext: " << text << '\n';
			break;
		}
		case 1: {
			cout << "\nEnter ciphertext: ";
			cin >> text;
			cout << "\nDecoding..\n";
			text = affineDecode(a, b, text);
			cout << "Plaintext: " << text << '\n';
		}
	}
	return 0;
}