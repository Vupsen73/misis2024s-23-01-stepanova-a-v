#include<iostream>
#include<string>


int main()
{
	std::string s;
	std::cin >> s;
	int ans = 0;
	for (int i = 0; i < s.length(); i++)
		if (s[i] == '4' or s[i] == '7')
		{
			ans++;
		}
	if (ans == 4 or ans == 7)
	{
		std::cout << "YES" << std::endl;
	}
	else
	{
		std::cout << "NO" << std::endl;
	}
	return 0;
}
