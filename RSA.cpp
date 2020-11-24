#include "CryptoMath.h"
#include <iostream>
#include <vector>
using namespace std;

int RSAMain() {
	long long int p, q, n, e, d;
	long long int plain;
	long long int cipher;
	long long int phi_n;
	cout << "RSA Encryption\n\n\n";
	
	cout << "Enter p: ";
	cin >> p;
	cout << "Enter q: ";
	cin >> q;

	n = p * q;
	phi_n = phi(n);

	cout << "\nn = " << n << '\n';
	cout << "phi(n) = " << phi_n << "\n\n";
	cout << "Enter e: ";
	cin >> e;

	if (gcd(e, phi_n) != 1) {
		cout << "Invalid choice of e";
		return -1;
	}

	cout << "Sending n and e to the public...\n" << endl;
	cout << "You received n and e" << endl;
	cout << "Enter plaintext (integer): ";
	cin >> plain;
	cout << "\nEncrypting..." << '\n';
	cipher = RSAEncrypt(n, e, plain);
	cout << "Ciphertext: " << cipher << '\n';
	cout << "Sending ciphertext..." << "\n\n";
	cout << "You received the ciphertext" << "\n";
	cout << "Decrypting...\n";
	plain = RSADecrypt(p, q, e, cipher);
	cout << "Decrypted message: " << plain << endl;
}