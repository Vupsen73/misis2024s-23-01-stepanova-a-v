#include <iostream>
using namespace std;
int main() {
	int x, a, b, c, k = 0;
	cin >> x;
	for (int i = 0; i < x; i++) {
		cin >> a >> b >> c;
		if (a + b + c > 1) {
			k++;
		}
	}
	cout << k;
}