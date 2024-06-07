#include<iostream>
#include<string>

int main()
{
	string a;
	string b;
	std::cin >> a >> b;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == b[i])
			a[i] = '0';
		else
			a[i] = '1';
	}
	std::cout << a;
}
