#include <iostream>

int main() {
	int a;
	int b;
	int count = 0;
	std::cin >> a >> b;
	while (a <= b) 
	{
		a = a * 3;
		b = b * 2;
		count = count + 1;
	}
	std::cout << count;
}
