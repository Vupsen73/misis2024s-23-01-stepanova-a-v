#include <iostream>

int main() {
	int n;
	int a;
	int b;
	int y = 0;
	int x = 0;
	std::cin >> n;
	for (int i = 1; i <= n; i++)
	{
		std::cin >> a >> b;
		x += b - a;

		if (x > y) 
		{
			y = x;
		}
	}
	std::cout << y;
}
