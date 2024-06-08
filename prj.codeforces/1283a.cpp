#include <iostream>

int main() 
{

	int n;
	std::cin >> n;

	while (n--) 
	{

		int a, b;
		std::cin >> a >> b;


		int m = (24 - a) * 60;
		std::cout << m - b << std::endl;
	}

}
