#include<iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int res = 0;
	int cnt = 0;
	while (n--)
	{
		char c;
		cin >> c;
		if (c == 'x')
		{
			if (cnt >= 2)
			{
				cnt++;
				res++;
			}
			else
			{
				cnt++;
			}
		}
		else
		{
			cnt = 0;
		}
	}
	cout << res;
	return 0;
}

