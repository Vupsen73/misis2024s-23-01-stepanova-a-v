#include <iostream>
using namespace std;
int main() {
	int n;
	int a, b;
	int y = 0;
	int x = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a >> b;
		x += b - a;

		if (x > y) {
			y = x;
		}
	}
	cout << y;
}