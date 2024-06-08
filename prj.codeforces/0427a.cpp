#include<iostream>

int main() 
{
	int a;
	int c = 0; 
	int d = 0;
	std::cin >> a;
	int b[a];
	for (int i = 0; i < a; i++) 
	{
		std::cin >> b[i];
		d += b[i];
		if (d < 0) 
		{
			c++;
			d = 0;
		}
	}
	std::cout << c;
}
