#include "CryptoMath.h"

int AffineAttacksMain() {
	int choice;
	int a, b;
	int a2, b2;
	string text;
	string ciphertext;
	string plaintext;
	cout << "Affine Cipher Attacks\n\n";
	cout << "1. Ciphertext only\n"
		"2. Known plaintext\n"
		"3. Chosen plaintext\n"
		"4. Chosen ciphertext\n";

	cout << "Choice: ";
	cin >> choice;
	

	switch (choice) {
		case 1: {
			cout << "This mode searches for all possible input to give the entered ciphertext. This application does not handle the algorithm of determining which"
				<< "of these inputs are actually english words, so the user must look through the 312 possible combinations.\n\n";
			cout << "Enter ciphertext: ";
			cin >> text;

			affineAttackCiO(text);
			break;
		}
		case 2: {
			cout << "Enter plaintext (atleast 2 letters): ";
			cin >> plaintext;
			cout << "Enter ciphertext: ";
			cin >> ciphertext;
			
			affineAttackKP(plaintext, ciphertext, a, b);
			
			if (a == -1) {
				cout << "Need more letters to use this method\n";
			}
			else {
				cout << "\nKEY\na: " << a << "\nb: " << b << '\n';
			}
			break;
		}
		case 3: {
			cout << "Enter key for encryption function. These are what we are going to attack\n";
			cout << "a: ";
			cin >> a2;
			cout << "b: ";
			cin >> b2;
			affineAttackChP(a, b, a2, b2);
			cout << "\nUsing 'ab' as plaintext. Attacking...\n";
			cout << "new a: " << a << "\nnew b: " << b << '\n';

			(a == a2 && b == b2) ? cout << "\nKeys match\n" : cout << "\nKeys don't match\n";
			break;
		}
		case 4: {
			cout << "Enter key for encryption function. These are what we are going to attack\n";
			cout << "a: ";
			cin >> a2;
			cout << "b: ";
			cin >> b2;
			affineAttackChP(a, b, a2, b2);
			cout << "\nUsing 'AB' as ciphertext. Attacking...\n";
			cout << "new a: " << a << "\nnew b: " << b << '\n';

			(a == a2 && b == b2) ? cout << "\nKeys match\n" : cout << "\nKeys don't match\n";
			break;
		}
	}
	return 0;
}