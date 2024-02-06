#include <iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	int god = n;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	n = god;
	while (!( a != b && a != c && a != d && b != c && b != d && c != d)) {
		god += 1;
		a = (god % 10000) / 1000;
		b = (god % 1000) / 100;
		c = (god % 100) / 10;
		d = god % 10;
		
	}
		cout << god;

	return 0;
}