#include<iostream>
#include<string>

int main()
{
	int t;
	std::cin >> t;
	while (t--)
	{
		std::string s;
		std::cin >> s;
		int l = s.size();
		if (l <= 10)
			std::cout << s << std::endl;
		else
		{
			std::cout << s[0] << l - 2 << s[l - 1] << std::endl;
		}
	}
	return 0;
}
