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
		int cnt = 0;
		for (int i = 0; i < 5; i++) 
		{
			if (s[i] == 'A') 
			{
				cnt++;
			}
		}
		if (cnt >= 3) 
		{
			std::cout << "A" << std::endl;
		}
		else 
		{
			std::cout << "B" << std::endl;
		}
	}

}