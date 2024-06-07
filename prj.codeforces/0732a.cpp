#include <iostream>

int main()
{
	int x = 1;
	int y = 1;
	int i = 1;
	std::cin >> x >> y;
	while (x * i % 10 != 0 && x * i % 10 != y)
	{
		i++;
	}
	std::cout << i;

	return 0;

}