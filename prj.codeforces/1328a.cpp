#include<iostream>

int main()
{
	int t;
	std::cin >> t;
	int a;
	int b;
	for (int i = 0; i < t; i++)
	{
		std::cin >> a >> b;
		if (a % b == 0)
		{
			std::cout << 0 << std::endl;
		} else
		{
			std::cout << b - (a % b) << std::endl;
		}
	}
}