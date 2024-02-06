#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	double a, b, c;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a >> b >> c;
		double t;
		t = (abs(a - b) / 2) / c;
		ceil(t);
		cout << ceil(t);
		cout << endl;

	}
}
