#include<iostream>

int main() 
{
	int a[1001];
	int t;
	std::cin >> t;
	for (int i = 0; i < t; i++) 
	{
		std::cin >> a[i];
	}
	int k = 0; 
	int max = a[0];
	int min = a[0];
	for (int i = 1; i < t; i++) 
	{
		if (a[i] < min) 
		{
			k++;
			min = a[i];
		}
		if (a[i] > max) 
		{
			k++;
			max = a[i];
		}
	}
	std::cout << k << std::endl;
}
