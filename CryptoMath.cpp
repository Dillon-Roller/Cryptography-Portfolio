#include "CryptoMath.h"

string affineEncode(int a, int b, string text) {
	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	text = upper(text);
	for (int i = 0; i < (int)text.size(); i++) {
		text[i] = A[((text[i] - 'A') * a + b) % 26];
	}
	return text;
}

string affineDecode(int a, int b, string text) {
	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	text = upper(text);
	int a_inv = modInverse(a, 26);
	if (a_inv == -1) {
		return "Inverse of a mod 26 does not exist";
	}

	for (int i = 0; i < (int)text.size(); i++) {
		text[i] = A[a_inv * ((text[i] - 'A') - b + 26) % 26];
	}
	return text;
}

void affineAttackCiO(string text) {
	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	text = upper(text);

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (gcd(i, 26) == 1) {
				cout << affineDecode(i, j, text) << '\n';
			}
		}
	}

}

void affineAttackKP(string plain, string cipher, int& a, int& b) {
	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	plain = upper(plain);
	cipher = upper(cipher);

	int coeff, res;

	//map two letters from plaintext to ciphertext to determine a and b
	for (int i = 0; i < (int)plain.size() - 1; i++) {
		coeff = ((plain[i] - 'A') - (plain[i + 1] - 'A') + 26) % 26;
		res = ((cipher[i] - 'A') - (cipher[i + 1] - 'A') + 26) % 26;

		if (gcd(coeff, 26) == 1) {
			a = (res * modInverse(coeff, 26)) % 26;
			b = (((cipher[i] - 'A') - (((plain[i] - 'A') * a) + 26) % 26) + 26) % 26;
			return;
		}
	}
	a = -1;
	b = -1;
	return;
}

void affineAttackChP(int& a, int& b, int a2, int b2) {
	string cipher = affineEncode(a2, b2, "ab");
	b = (cipher[0] - 'A' + 26) % 26;
	a = ((cipher[1] - 'A') - b + 26) % 26;
	return;
}

void affineAttackChC(int& a, int& b, int a2, int b2) {
	string plain = affineDecode(a2, b2, "ab");
	b = (plain[0] - 'A' + 26) % 26;
	a = ((plain[1] - 'A') - b + 26) % 26;
	return;
}

string upper(string text) {
	for (auto& c : text) {
		c = toupper(c);
	}
	return text;
}

int gcdExtended(int a, int b, int& x, int& y)
{
	if (a == 0)
	{
		x = 0;
		y = 1;
		return b;
	}

	int x1;
	int y1;
	int gcd = gcdExtended(b % a, a, x1, y1);

	x = y1 - x1 * (b / a);
	y = x1;

	return gcd;
}

int modInverse(int a, int m) {

	int x, y;
	int gcd = gcdExtended(a % m, m, x, y);

	if (gcd != 1) {
		return -1;
	}

	return (x + m) % m; //handles negative values
}

int isPrimitive(int a, int m) {
	//fix
	return gcd(a, phi(m)) == 1;
}

long long int phi(long long int n)
{
	long long int result = n; 

	for (long long int p = 2; p * p <= n; ++p) {
		if (n % p == 0) {
			while (n % p == 0)
				n /= p;
			result -= result / p;
		}
	}
	if (n > 1)
		result -= result / n;
	return result;
}

int gcd(int a, int b){
	if (a == 0)
		return b;
	return gcd(b % a, a);
}

string vigenereEncrypt(string text, string key) {
	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	text = upper(text);
	key = upper(key);
	for (int i = 0; i < (int)text.size(); i++) {
		text[i] = A[((text[i] - 'A') + (key[i % (int)key.size()] - 'A')) % 26];
	}
	return text;
}

string vigenereDecrypt(string text, string key) {
	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	text = upper(text);
	key = upper(key);
	for (int i = 0; i < (int)text.size(); i++) {
		text[i] = A[((text[i] - 'A') - (key[i % (int)key.size()] - 'A') + 26) % 26];
	}
	return text;
}

int vigenereAttackKeyLength(string text) {
	text = upper(text);
	vector<int> coincidences;
	int sum = 0;
	int displacement = 1;
	while (displacement < (int)text.size()) {
		sum = 0;
		for (int i = 0; i + displacement < (int)text.size(); i++) {
			if (text[i] == text[i + displacement]) {
				sum++;
			}
		}
		coincidences.push_back(sum);
		displacement++;
	}

	for (int i = 0; i < (int)coincidences.size(); i++) {
		cout << coincidences[i] << " ";
	}

	int max = coincidences[0];
	int max_ind = 0;
	for (int i = 0; i < (int)coincidences.size(); i++) {
		if (coincidences[i] > max) {
			max = coincidences[i];
			max_ind = i;
		}
	}
	return max_ind + 1;
}

string vigenereAttackKey(string text, int length) {
	const vector<double> FREQ_ENG = { .082, .015, .028, .043, .127, .022, .020, .061, .070, .002, .008, .040, .024,
		.067, .075, .019, .001, .060, .063, .091, .028, .010, .023, .001, .020, .001 };

	const string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	text = upper(text);
	
	int sum;
	string result;
	int count = 0;
	while (count < length) {
		vector<double> v;
		
		for (int i = 0; i < 26; i++) {
			sum = 0;
			for (int j = 0 + count; j < (int)text.size(); j += length) {
				if (text[j] == A[i]) {
					sum++;
				}
			}
			v.push_back(sum);
		}
		
		for (auto& x : v) {
			x /= (int)text.size();
		}

		vector<double> dotProducts;

		for (int i = 0; i < 26; i++) {
			dotProducts.push_back(dotProd(v, shiftVectorRight(FREQ_ENG, i)));
		}

		double max = dotProducts[0];
		int max_ind = 0;
		for (int i = 0; i < (int)dotProducts.size(); i++) {
			if (dotProducts[i] > max) {
				max = dotProducts[i];
				max_ind = i;
			}
		}
		
		result.push_back(A[max_ind]);
		count++;
	}
	return result;
}

vector<double> shiftVectorRight(const vector<double>& vec, int num) {
	if (num == 0) return vec;

	vector<double> newvec;
	int count = 0;
	int i = vec.size() - num;
	while (count < (int)vec.size()) {
		newvec.push_back(vec[i % (int)vec.size()]);
		count++;
		i++;
	}
	return newvec;
}

vector<double> freq(string text) {
	string A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	text = upper(text);
	vector<double> result(26, 0);

	for (int i = 0; i < (int)text.size(); i++) {
		result[text[i] - 'A']++;
	}
	for (int i = 0; i < 26; i++) {
		result[i] /= (int)text.size();
	}

	return result;
}

double dotProd(const vector<double>& v1, const vector<double>& v2) {
	double sum = 0;
	for (int i = 0; i < (int)v1.size(); i++) {
		sum += v1[i] * v2[i];
	}
	return sum;
}

long long int modPow(long long int a, long long int n, long long int m) {
	int res = 1;
	while (n--) {
		res = (res * a) % m;
	}
	return res;
}

long long int RSAEncrypt(long long int n, long long int e, long long int plain) {
	return modPow(plain, e, n);
}

long long int RSADecrypt(long long int p, long long int q, long long int e, long long int message) {
	long long int d, n;

	n = p * q;
	d = modInverse(e, (p-1)*(q-1));

	return modPow(message, d, n);
}

void factor(long long int n, long long int m) {
	if (m == 0) fermatFactor(n);
	if (m == 1) rhoFactor(n);
	if (m == 2) pMinusOneFactor(n);
}

void fermatFactor(long long int n) {
	long long int a, b;

	a = ceil(sqrt(n));
	b = (a * a) - n;

	while (!isPerfectSquare(b)) {
		a = a + 1;
		b = (a * a) - n;
	}

	cout << n << " = " << long long int(a - sqrt(b)) << " * " << long long int(a + sqrt(b));
}

void rhoFactor(long long int n) {
	long long int x, y, d;

	x = 2;
	y = 2;
	d = 1;

	while (d == 1) {
		x = g(x, n);
		y = g(g(y, n), n);
		d = gcd(abs(x - y), n);
	}

	if (d == n) {
		cout << "Could not factor" << endl;
	}
	else {
		cout << d << " is a non-trivial factor of " << n << endl;
	}
}

void pMinusOneFactor(long long int n) {
	int b = 5;
	int m = 60;
	int a = 2;
	int g = gcd(pow(a, m) - 1, n);
	if (g > 1 && g < n) {
		cout << g << " is a factor" << endl;
	}
	else
		cout << "Failure" << endl;
}

bool isPerfectSquare(double x) {
	return ((sqrt(x) - floor(sqrt(x)) == 0));
}

int g(long long int x, long long int n) {
	return (x * x + 1) % n;
}

vector<int> strToVec(string num) {
	vector<int> res;

	for (int i = 0; i < (int)num.size(); i++) {
		if (num[i] == '0')
			res.push_back(0);
		else
			res.push_back(1);
	}
	return res;
}

string vecToStr(vector<int> num) {
	string res = "";

	for (int i = 0; i < (int)num.size(); i++) {
		if (num[i] == 0)
			res += '0';
		else
			res += '1';
	}
	return res; 
}

string roundKey(string num, int round) {
	string shifted = "00000000";
	for (int i = 0; i < 8; i++) {
		shifted[i] = num[(i + round - 1) % (int)num.size()];
	}
	return shifted;
}

string expander(string num) {
	string res = "00000000";
	res[0] = num[0];
	res[1] = num[1];
	res[2] = num[3];
	res[3] = num[2];
	res[4] = num[3];
	res[5] = num[2];
	res[6] = num[4];
	res[7] = num[5];
	return res;
}

string DEShelper(string msg, string K, int num_rounds) {
	string newMsg = "000000000000";
	string L0 = "000000";
	string R0 = "000000";
	string roundkey = "00000000";
	L0 = msg.substr(0, 6);
	R0 = msg.substr(6, 6);
	
	for (int i = 1; i <= num_rounds; i++) {
		roundkey = roundKey(K, i);
		
		newMsg = DES(L0, R0, roundkey);
		
		L0 = newMsg.substr(0, 6);
		R0 = newMsg.substr(6, 6);
	}
	return L0 + R0;
}

string DES(string L, string R, string K) {
	string Li, Ri, res;

	res = f(R, K);
	
	Li = R;

	Ri = XOR(L, res);
	
	return Li + Ri;
}

string f(string R, string K) {

	string Sbox[2][8] = {
		{"101", "010", "001", "110", "011", "100", "111", "000"},
		{"001", "100", "110", "010", "000", "111", "101", "001"}
	};

	string Sbox2[2][8] = {
		{"100", "000", "110", "101", "111", "001", "011", "010"},
		{"101", "011", "000", "111", "110", "010", "001", "100"}
	};

	string S, newR;
	string S1, S2, S1result, S2result;

	newR = expander(R);
	S = XOR(newR, K);
	
	S1 = S.substr(0, 4);
	S2 = S.substr(4, 4);

	S1result = Sbox[stoi(S1.substr(0, 1))][stoi(S1.substr(1, 3), 0, 2)];
	S2result = Sbox2[stoi(S2.substr(0, 1))][stoi(S2.substr(1, 3), 0, 2)];
	
	return S1result + S2result;
}

string XOR(string n1, string n2) {
	string res = "00000000";
	for (int i = 0; i < (int)n1.size(); i++) {
		
		if ((n1[i] == '0' && n2[i] == '0') || (n1[i] == '1' && n2[i] == '1'))
			res[i] = '0';
		else
			res[i] = '1';
	}
	return res;
}

bool isPrime(int n)
{
	if (n <= 1)  
		return false;

	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return false;

	return true;
}

int random_prime(int b) {
	int num = 4;
	while (!isPrime(num)) {
		num = rand() % (((int)pow(2, b + 1) - 1) - ((int)pow(2, b) - 1)) + ((int)pow(2, b) - 1);
	}
	return num;
}
