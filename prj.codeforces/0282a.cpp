#include<iostream>
#include<string>

int main() 
{
	int n = 0;
	int x = 0;
	std::cin >> n;
	for (int i = 0; i < n; i++) 
	{
		std::string str;
		std::cin >> str;
		if (str[1] == '+')
		{
			x++;
		}
		else
		{
			x--;
		}
	}
	std::cout << x << std::endl;
}
