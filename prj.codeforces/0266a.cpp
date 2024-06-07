#include<iostream>
#include<string>

int main()
{
	std::string s;
	int n;
	std::cin >> n;
	std::cin >> s;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == s[i + 1])
		{
			count++;
		}
	}
	std::cout << count;
}
