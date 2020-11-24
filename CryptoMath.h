#ifndef CRYPTOMATH_H_
#define CRYPTOMATH_H_
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

string affineEncode(int a, int b, string text);
string affineDecode(int a, int b, string text);
void affineAttackCiO(string text);
void affineAttackKP(string plain, string cipher, int& a, int& b);
void affineAttackChP(int& a, int& b, int a2, int b2);
void affineAttackChC(int& a, int& b, int a2, int b2);
string upper(string text);
int gcdExtended(int a, int b, int& x, int& y);
int gcd(int a, int b);
int modInverse(int a, int m);
int isPrimitive(int a, int m);
long long int phi(long long int m);
string vigenereEncrypt(string text, string key);
string vigenereDecrypt(string text, string key);
int vigenereAttackKeyLength(string text);
string vigenereAttackKey(string text, int length);
vector<double> freq(string text);
vector<double> shiftVectorRight(const vector<double>& vec, int num);
double dotProd(const vector<double>& v1, const vector<double>& v2);
long long int modPow(long long int a, long long int n, long long int m);
long long int RSAEncrypt(long long int n, long long int e, long long int plain);
long long int RSADecrypt(long long int p, long long int q, long long int e, long long int message);
void factor(long long int n, long long int m);
void fermatFactor(long long int n);
void rhoFactor(long long int n);
void pMinusOneFactor(long long int n);
bool isPerfectSquare(double x);
int g(long long int x, long long int n);
vector<int> strToVec(string num); 
string vecToStr(vector<int> num);
string roundKey(string num, int round);
string expander(string num);
string DEShelper(string msg, string K, int num_rounds);
string DES(string L, string R, string K);
string f(string R, string K);
string XOR(string n1, string n2);
bool isPrime(int n);
int random_prime(int b);
#endif
