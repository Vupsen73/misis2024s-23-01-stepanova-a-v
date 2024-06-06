#include <iostream>
using namespace std;
int main()
{
	double a, s = 0, n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a;
		s += (a / 100);
	}
	cout << s / n * 100 << endl;
	return 0;
}