#include<iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	string s;
	for (int i = 1; i <= n; i++)
	{
		if (i == 1)
			s = "I hate ";
		else if (i % 2 == 0)
		{
			s = s + "that I love ";
		}
		else
			s = s + "that I hate ";
	}
	cout << s << "it";
}