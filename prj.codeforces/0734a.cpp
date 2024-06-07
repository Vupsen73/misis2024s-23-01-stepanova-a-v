#include<iostream>
#include<string>

int main()
{
	int n;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	int c1 = 0;
	int c2 = 0;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == 'A')
		{
			c1++;
		}
		else
		{
			c2++;
		}
	}
	if (c1 > c2)
	{
		std::cout << "Anton";
	}
	else if (c2 > c1)
	{
		std::cout << "Danik";
	}
	else
	{
		std::cout << "Friendship";
	}
}
