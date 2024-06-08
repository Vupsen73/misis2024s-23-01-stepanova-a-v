#include<iostream>
#include<algorithm>

int main() 
{
	int n;
	int k;
	int l;
	int c;
	int d;
	int p;
	int nl;
	int np;
	std::cin >> n >> k >> l >> c >> d >> p >> nl >> np;
	int x = k * l;
	int y = x / nl;
	int z = c * d; 
	int m = p / np;
	std::cout << (std::min(std::min(y, z), m)) / n;
}