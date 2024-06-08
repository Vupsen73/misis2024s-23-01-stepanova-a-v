#include <iostream>

int main()
{
	int n;
	int t;
	std::cin >> n;
	for (int i = 0; i < n; i++) 
	{
		std::cin >> t;
		std::cout << (t / 2) + (t % 2) << std::endl;
	}
}