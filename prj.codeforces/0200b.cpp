#include <iostream>

int main()
{
	double n;
	double a;
	double s = 0;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		std::cin >> a;
		s += (a / 100);
	}
	std::cout << s / n * 100 << std::endl;
	
	return 0;
}
