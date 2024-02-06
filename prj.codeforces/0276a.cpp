#include <iostream>
#include<cmath>
using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	int p = -2000000000;
	for (int i = 0; i < n; i++)
	{
		int f, t;
		cin >> f >> t;
		if (t <= k)
		{
			p = max(p, f);
		}
		else
		{
			p = max(p, f - t + k);
		}
	}
	cout << p;
	
	return 0;
}