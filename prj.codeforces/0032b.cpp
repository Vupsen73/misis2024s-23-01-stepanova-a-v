#include<iostream>
#include<string>

int main() {
	std::string s;
	int i = 0;
	std::cin >> s;
	while (i < s.length()) 
	{
		if (s[i] == '.') 
		{
			std::cout << 0;
			i++;
		}else 
		{
			if (s[i + 1] == '-') 
			{
				std::cout << 2;
			}else 
			{
				std::cout << 1;
			}
			i += 2;
		}
	}
	return 0;
}
